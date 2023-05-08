#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <utility>
#include <vector>
#include <array>
#include <functional>
#include <any>
#include <variant>
#include <bitset>

#include <boost/algorithm/minmax.hpp>
#include <boost/utility.hpp>
#include <boost/optional.hpp>
#include <boost/assign.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <boost/multi_array.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/version.hpp>
#include <boost/timer.hpp>
#include <boost/noncopyable.hpp>
#include <boost/format.hpp>

template<typename T>
void testOptions(boost::optional<T> &op) {
    if (op.has_value()) {
        std::cout << "op: " << op.get() << std::endl;
    } else {
        std::cout << "op has no value" << std::endl;
    }
}

#define print(x) do{std::cout << (x) << std::endl;}while(0);

using Tag = std::string;

class Metric {
public:
    Metric(std::string name) : name_(std::move(name)) {}

    ~Metric() {
        std::for_each(tags_.begin(), tags_.end(), [](auto &tag) { std::cout << tag << std::endl; });
    }

    void addTag(const Tag &tag) {
        tags_.push_back(tag);
    }

private:
    std::string name_;
    std::vector<Tag> tags_;
};

#define define_metric(name, ...) \
    std::unique_ptr<Metric> name = create_metric(#name, {__VA_ARGS__})

template<typename... Args>
std::unique_ptr<Metric> create_metric(const std::string &name, const std::initializer_list<Tag> &tags) {
    auto metric = std::make_unique<Metric>(name);
    for (const auto &tag: tags) {
        metric->addTag(tag);
    }
    return metric;
}


int main() {
    auto x = std::minmax({1, 2, 3, 4, 5, 6});
    std::cout << std::get<0>(x) << " " << std::get<1>(x) << std::endl;
    auto y = boost::minmax(1, 2);
    std::cout << get<0>(y) << " " << get<1>(y) << std::endl;
    boost::optional<int> op0;
    boost::optional<int> op1(boost::none_t);
    testOptions(op0);
    using namespace boost::assign;
    std::vector<int> v;
    v += 1, 2, 3, 4, 5, 6 * 6;
    std::for_each(v.begin(), v.end(), [](const int &n) { std::cout << n << " "; });
    std::array<int, 10> a1{}, a2{};
    a1.fill(1), a2.fill(2);
    std::swap(a1, a2);
    std::copy(a1.begin(), a1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    std::copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    std::string s0("boost");
    boost::to_upper(s0);
    std::cout << s0 << std::endl;
    std::cout << boost::to_lower_copy(s0) << std::endl;
    boost::to_lower(s0);
    std::cout << boost::starts_with(s0, "bo") << std::endl;
    s0.append("       ");
    s0.insert(0, "      ");
    print(s0)
    boost::trim_left(s0);
    boost::trim_right(s0);
    print(s0)
    boost::dynamic_bitset<> db1(100);
    print(db1.to_ulong())
    db1.set(0, true);
    print(db1.to_ulong())
    print(db1.count())
    boost::circular_buffer<int> cb(3);
    for (int i = 0; i < 10; ++i) cb.push_back(i);
    for (const auto &x: cb) {
        print(x)
    }
    boost::any any1(100);
    print(boost::any_cast<int>(any1))
    print(any1.type().name())

    boost::variant<int, std::string> var1;
    var1 = 100;
    print(boost::get<int>(var1))
    var1 = "string";
    print(boost::get<std::string>(var1))
    print(var1.type() == typeid(std::string))

    boost::multi_array<int, 3> ma(boost::extents[2][3][4]);
    print(ma.num_dimensions())
    print(ma.num_elements())
    uint8_t u8t = 1;
    print(std::to_string(u8t))
    std::bitset<8> bits(u8t);
    print(bits.to_string())

    boost::variant<int, std::string> var2;
    var2 = 12345;
    var2 = std::to_string(boost::get<int>(var2));
    print(var2)
    class A {
    public:
        A(int _x) : x(_x) {}

        [[nodiscard]] std::string ToString() const {
            return std::to_string(x);
        }

    private:
        int x{0};
    };
    boost::variant<std::string, A> var3;

    var3 = A(42);
    var3 = boost::get<A>(var3).ToString();
    print(boost::get<std::string>(var3))
    using tvar = boost::variant<std::string, A>;
    std::vector<tvar> vs{};
    for (int i = 0; i < 10; ++i) {
        vs.emplace_back(A(i));
    }
    boost::range::for_each(vs, [](tvar &t) {
        t = boost::get<A>(t).ToString();
        print("vs: " + boost::get<std::string>(t))
    });

    print(BOOST_VERSION)
    print(BOOST_PLATFORM)

    boost::timer ts;
    print(ts.elapsed())
    print(std::clock())

    class Nocopy : boost::noncopyable {
    };

    print(__FUNCTION__)

    auto fmts = boost::format("%s:%d+%d=%d") % "sum" % 1 % 2 % (1 + 2);
    std::string fmtstr = fmts.str();
    print(fmts)
    print(fmtstr)

    boost::replace_first(fmtstr, "sum", "sub");
    print(fmtstr)

    std::string ss = "A lockdown starts when the number of sick people reaches 20000. This results in a reduction of new infections by 36%. The lockdown ends when the number of sick people falls below 6000 again";
    std::vector<std::string> dstr;
    boost::ifind_all(dstr, ss, "in");
    print(dstr.size())
    dstr.clear();
    // Input string
    std::string input = "This is a sample string to be split.";
    // Create a vector to store the split parts
    std::vector<std::string> result;
    // Split the input string using spaces as delimiters
    boost::algorithm::split(result, input, boost::is_space());
    // Print the split parts
    for (const auto &part: result) {
        print(part)
    }

    std::string joinStr = boost::algorithm::join(result, " ");
    print(joinStr)

    class VA {
    public:
        VA() = default;

        auto &Get() const {
            return va;
        }

    private:
        std::vector<int> va{1, 2, 3, 4, 5};
    };

    VA va{};
    const auto &vav = va.Get();
    boost::for_each(vav, [](const auto &x) { print(x) });

    Tag tag1{"Hello"}, tag2{"World"};

    // Define a metric with no tags
    define_metric(metric1);

    // Define a metric with tags
    define_metric(metric2, tag1, tag2);

}