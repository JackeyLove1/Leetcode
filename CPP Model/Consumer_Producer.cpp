#include <unistd.h>

#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static const int bufSize = 8; // Item buffer size.
static const int ProNum = 20;   // How many items we plan to produce.

struct resource {
	int buf[bufSize]; // 产品缓冲区, 配合 read_pos 和 write_pos 模型环形队列.
	size_t read_pos; // 消费者读取产品位置.
	size_t write_pos; // 生产者写入产品位置.
	size_t pro_item_counter;
	size_t con_item_counter;
	std::mutex mtx; // 互斥量,保护产品缓冲区
	std::mutex pro_mtx;
	std::mutex con_mtx;
	std::condition_variable not_full; // 条件变量, 指示产品缓冲区不为满.
	std::condition_variable not_empty; // 条件变量, 指示产品缓冲区不为空.
} instance; // 产品库全局变量, 生产者和消费者操作该变量.

typedef struct resource resource;


void Producer(resource *ir, int item)
{
	std::unique_lock<std::mutex> lock(ir->mtx);
	while (((ir->write_pos + 1) % bufSize)
		== ir->read_pos) { // item buffer is full, just wait here.
		std::cout << "Producer is waiting for an empty slot...\n";
		(ir->not_full).wait(lock); // 生产者等待"产品库缓冲区不为满"这一条件发生.
	}

	(ir->buf)[ir->write_pos] = item; // 写入产品.
	(ir->write_pos)++; // 写入位置后移.

	if (ir->write_pos == bufSize) // 写入位置若是在队列最后则重新设置为初始位置.
		ir->write_pos = 0;

	(ir->not_empty).notify_all(); // 通知消费者产品库不为空.
}

int Consumer(resource *ir)
{
	int data;
	std::unique_lock<std::mutex> lock(ir->mtx);
	// item buffer is empty, just wait here.
	while (ir->write_pos == ir->read_pos) {
		std::cout << "Consumer is waiting for items...\n";
		(ir->not_empty).wait(lock); // 消费者等待"产品库缓冲区不为空"这一条件发生.
	}

	data = (ir->buf)[ir->read_pos]; // 读取某一产品
	(ir->read_pos)++; // 读取位置后移

	if (ir->read_pos >= bufSize) // 读取位置若移到最后，则重新置位.
		ir->read_pos = 0;

	(ir->not_full).notify_all(); // 通知消费者产品库不为满.

	return data; // 返回产品.
}


void ProducerTask() // 生产者任务
{
	bool ready_to_exit = false;
	while (1) {
		sleep(1);
		std::unique_lock<std::mutex> lock(instance.pro_mtx);
		if (instance.pro_item_counter < ProNum) {
			++(instance.pro_item_counter);
			Producer(&instance, instance.pro_item_counter);
			std::cout << "Producer thread " << std::this_thread::get_id()
				<< " is producing the " << instance.pro_item_counter
				<< "^th item" << std::endl;
		}
		else 
			ready_to_exit = true;
		lock.unlock();
		if (ready_to_exit == true) 
			break;
	}
	std::cout << "Producer thread " << std::this_thread::get_id()
		<< " is exiting..." << std::endl;
}

void ConsumerTask() // 消费者任务
{
	bool ready_to_exit = false;
	while (1) {
		sleep(1);
		std::unique_lock<std::mutex> lock(instance.con_mtx);
		if (instance.con_item_counter < ProNum) {
			int item = Consumer(&instance);
			++(instance.con_item_counter);
			std::cout << "Consumer thread " << std::this_thread::get_id()
				<< " is consuming the " << item << "^th item" << std::endl;
		}
		else
			ready_to_exit = true;
		lock.unlock();
		if (ready_to_exit == true)
			break;
	}
	std::cout << "Consumer thread " << std::this_thread::get_id()
		<< " is exiting..." << std::endl;
}

void Initresource(resource *ir)
{
	ir->write_pos = 0; // 初始化产品写入位置.
	ir->read_pos = 0; // 初始化产品读取位置.
	ir->pro_item_counter = 0;
	ir->con_item_counter = 0;
}

int main()
{
	Initresource(&instance);
	std::thread producer1(ProducerTask);
	std::thread producer2(ProducerTask);
	std::thread producer3(ProducerTask);
	std::thread producer4(ProducerTask);

	std::thread consumer1(ConsumerTask);
	std::thread consumer2(ConsumerTask);
	std::thread consumer3(ConsumerTask);
	std::thread consumer4(ConsumerTask);

	producer1.join();
	producer2.join();
	producer3.join();
	producer4.join();

	consumer1.join();
	consumer2.join();
	consumer3.join();
	consumer4.join();
	return 0;
}
