import axios, { AxiosError, AxiosResponse } from 'axios';
import token from './somewhere';

interface Todo {
  id: string;
  title: string;
}

interface User {
  id: string;
  name: string;
}

axios.defaults.baseURL = 'https://jsonplaceholder.typicode.com';

axios.interceptors.request.use((config) => {
  if (token) {
    config.headers.Authorization = `Bearer ${token}`;
  }
  return config;
});

axios.interceptors.response.use(
  (res) => res,
  (error: AxiosError) => {
    const { data, status, config } = error.response!;
    switch (status) {
      case 400:
        console.error(data);
        break;

      case 401:
        console.error('unauthorised');
        break;

      case 404:
        console.error('/not-found');
        break;

      case 500:
        console.error('/server-error');
        break;
    }
    return Promise.reject(error);
  }
);

const responseBody = <T>(response: AxiosResponse<T>) => response.data;

const request = {
  get: <T>(url: string) => axios.get<T>(url).then(responseBody),
  post: <T>(url: string, body: {}) =>
    axios.post<T>(url, body).then(responseBody),
};

const todos = {
  list: () => request.get<Todo[]>('/todos'),
  details: (id: string) => request.get<Todo>(`/todos/${id}`),
  create: (data: Todo) => request.post<void>('/todos', data),
};

const users = {
  list: () => request.get<User[]>('/users'),
  details: (id: string) => request.get<User>(`/users/${id}`),
  create: (data: User) => request.post<User>('/users', data),
};

const api = {
  todos,
  users,
};

export default api;