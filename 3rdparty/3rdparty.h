#ifndef _ROUCHIE_BIGDOG_H_
#define _ROUCHIE_BIGDOG_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <regex>
#include <atomic>
#include <algorithm>
#include <utility>
#include <memory>

#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <map>
#include <unordered_map>
#include <stack>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//{
    // 用来测试类名，挺好用的，直接定义 TD<decltype(z)> td; 即可以看编译报错，就知道z到底是什么类型了
    template<typename T> // 声明TD
    class TD;            // TD == "Type Displayer"

	#define THROW(ABC, ...) {                                                                \
        std::string e = fmt::format("throw [{}:{}] " ABC, __FILE__, __LINE__, ##__VA_ARGS__);\
		SPDLOG_ERROR("{}", e);                                                               \
		throw std::runtime_error(e);                                                         \
	}

    #define ssp(n) std::this_thread::sleep_for(std::chrono::seconds(n))
    #define msp(n) std::this_thread::sleep_for(std::chrono::milliseconds(n))
    #define usp(n) std::this_thread::sleep_for(std::chrono::microseconds(n))

    inline uint64_t getUS()
	{
		auto tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
        return tp.time_since_epoch().count();
	}

    inline bool isMask(std::string s)
    {
        std::regex reg{"^((128|192)|2(24|4[08]|5[245]))(\\.(0|(128|192)|2((24)|(4[08])|(5[245])))){3}$"};
        return std::regex_match(s, reg);
    }

	inline bool isIP(std::string s)
	{
        // std::regex reg{"((25[0-4]|2[0-4]\\d|[0-1]\\d{2}|\\d{1,2})\\.){3}(25[0-4]|24\\d|[0-1]\\d{2}|\\d{1,2})"};
        std::regex reg{"((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"};
		return std::regex_match(s, reg);
	}

	inline bool isIP(const char* s)
	{
		return isIP(std::string(s));
	}

	/*
	 * 判断系统大小端
	 * */
	inline bool isBigEndian()
	{
		union {
			short s;
			char c[sizeof(short)];
		} un;

		un.s = 0x1234;
		if (0x34 == un.c[0]) return false;
		else return true;
	}
	
	//{ display 显示16进制数
        inline void display(const char* title, uint8_t* buf, int len)
        {
			int i = 0;
	
			// 一行打印的长度
			char name[128];
			char dname[128] = {0};
	
			int kk = snprintf(name, sizeof(name), " [%s] len=%d ", title, len);
			if (kk < 68) {
				i = (68 - kk) / 2;
				memset(dname, '-', i);
				memcpy(dname + i, name, kk);
				memset(dname + i + kk, '-', i+(kk%2));
			}
	
			printf("\n%s\n", dname);
	
			for (i = 0; i < len; i++) {
				printf("%02X ", (unsigned char)buf[i]);
				if ((i + 1) % 8 == 0) {
					printf("  ");
				}
	
				if ((i == (len - 1)) || ((i + 1) % 16 == 0)) {
					int j = 0;
					for (j = i % 16 + 1; j < 16; j++) {
						printf("   ");
	
						if ((j + 1) % 8 == 0) {
							printf("  ");
						}
					}
	
					for (j = i - i % 16; j <= i; j++) {
                        if (buf[j] > 33 && buf[j] < 128) {
							printf("%c", buf[j]);
						} else {
							printf(".");
						}
					}
				}
	
				if (((i+1) != len) && ((i + 1) % 16 == 0)) {
					printf("\n");
				}
			}
	
			printf("\n--------------------------------------------------------------------\n");
		}

        inline void display(const char* title, const char* buf, int len)
        {
            display(title, (uint8_t *) buf, len);
        }

        inline void display(const char* title, void* buf, int len)
        {
            display(title, (uint8_t *) buf, len);
        }
    //}
//}

//{
#ifdef SPDLOG
	// SPDLOG 库，在 SPDLOG 中需要输出 {} 则可以使用 {{ 和 }} 来分别输出 { 和 }
    // 打印地址，SPDLOG_DEBUG("{:p} {:x}", fmt::ptr(p), *p);
    // SPDLOG_DEBUG("{0:>8d} {0:<8x} {0:08X} {1:X}", 123, 0x123);
    // 这里的0，1表示第0、1个参数，>表示右对齐，<表示左对齐
    // SPDLOG_DEBUG("{0:─^20} {1:#^{2}} {0:#^20}", "", "hello", 100);
    // 用来打印多个重复字符

	#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

	#include "spdlog/spdlog.h"
	#include "spdlog/fmt/bin_to_hex.h"
    #include "spdlog/sinks/rotating_file_sink.h"
	#include "spdlog/sinks/stdout_color_sinks.h"
	#include "spdlog/fmt/bin_to_hex.h"
	#include "spdlog/sinks/basic_file_sink.h"

	inline void spdlog_init(spdlog::level::level_enum log_level = spdlog::level::trace, const std::string logger_name = "", const std::string filename = "", bool release = false)
	{
		spdlog::set_level(log_level); // Set specific logger's log level
		// spdlog::set_pattern("%^[%H:%M:%S.%f] [%t:%L(%s:%#)]%$ %v");
		spdlog::set_pattern("[%H:%M:%S.%f] [%^%L:(%s:%#)%$] %v");

		if (release) {
			auto max_size = 1024 * 1024 * 1;
			auto max_files = 3;
			auto logger = spdlog::rotating_logger_mt(logger_name, filename, max_size, max_files);
			// 设置立即刷新级别，默认写文件会缓存，也可以调用 flush 函数刷新
			logger->flush_on(spdlog::level::warn);
			spdlog::set_default_logger(logger);
		}

		SPDLOG_DEBUG("__build time__: [{} {}]", __DATE__, __TIME__);
	}

    inline void spdlog_init_v2(spdlog::level::level_enum log_level = spdlog::level::trace, const std::string filename = "spdlog.txt")
	{
        auto max_size = 1024 * 1024 * 1;
        auto max_files = 3;

        auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto rotating = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filename, max_size, max_files);

        std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>("all", spdlog::sinks_init_list({console, rotating}));
        logger->set_level(log_level);
        logger->set_pattern("[%H:%M:%S.%f] [%^%L:(%s:%#)%$] %v");
        spdlog::set_default_logger(logger);

        SPDLOG_DEBUG("__build time__: [{} {}]", __DATE__, __TIME__);
    }

	inline void spdlog_level(uint32_t level)
	{
        spdlog::set_level((spdlog::level::level_enum) level);
	}

	inline void spdlog_flush()
	{
		spdlog::get("all")->flush();
	}
#endif
//}

//{ nlohmann json 库
#ifdef NLOHMANN
    // const char *m = R"({"name":"rouchie", "age":32, "count": 1024})";
    // json j = json::parse(m, m+strlen(m));
    // json::array() 一个空数组

	#include "nlohmann/json.hpp"

	using json = nlohmann::json;

    inline json parseJson(std::string s)
	{
		json j;

        if (s.empty()) return j;

		try {
			j = json::parse(s);
		} catch(...) {
			SPDLOG_ERROR("json parse failed");
            display("json error", (const char *) s.data(), s.size());
		}

		return j;
	}

    template <typename T>
    inline json parseJson(const T * msg, size_t len)
    {
        std::string s((const char *) msg, len);
        return parseJson(s);
    }

	inline json get(std::string name)
	{
		std::ifstream in(name);

		if (!in.is_open()) return json();

		json j;

		try {
			in >> j;
		} catch(...) {}

		in.close();

		return j;
	}

	inline void set(json j, std::string name)
	{
		std::ofstream out(name);

		if (!out.is_open()) {
			SPDLOG_CRITICAL("json write failed [{}]", name);
			return;
		}

		out << j.dump(4) << std::endl;
		out.close();
	}

    template <typename T>
    T get(json j, std::string name, T tDefVal)
	{
		if (j[name].is_null()) return tDefVal;

		T t;
		try {
			t = j[name].get<T>();
		}
		catch (nlohmann::detail::exception & e) {
            SPDLOG_CRITICAL("{} ({}) {}", j.dump(), name, e.what());
			t = tDefVal;
		}

		return t;
	}

    template <typename T>
    T item(std::string file, std::string name, T tDefVal)
    {
        json j = get(file);

        return get<T>(j, name, tDefVal);
    }
#endif
//}

//{
#ifdef UUID
	#include "uuid/uuid.h"
	inline std::string uuid()
	{
		uuid_t uuid;
		char s[128];
		uuid_generate(uuid);
		uuid_unparse(uuid, s);

		return std::string(s);
	}
#endif
	//}

	//{ 使用互斥锁和条件变量做信号量
	class CSemaphore
	{
	public:
        explicit CSemaphore(unsigned int count = 0) : m_count(count) {

		}

		void post() {
			std::unique_lock<std::mutex> lock(_mutex);
			++m_count;
			_cv.notify_one();
		}

		void wait() {
			std::unique_lock<std::mutex> lock(_mutex);
			_cv.wait(lock, [=] {return m_count > 0; });
			--m_count;
		}

        bool trywait() {
            std::unique_lock<std::mutex> lock(_mutex);
            if (m_count <= 0) return false;

            _cv.wait(lock, [=] {return m_count > 0; });
            --m_count;
            return true;
        }

	private:
		std::mutex _mutex;
		std::condition_variable _cv;
		unsigned int m_count;
	};
//}

//{ 线程间通信
    template <typename T>
    class CShpQueue {
    public:
        CShpQueue() {
        }

        void push(std::shared_ptr<T> msg) {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_queue.push(msg);
            m_sem.post();
			m_size++;
        }

        void push(std::shared_ptr<T> msg, std::function<void()> f) {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_queue.push(msg);
            m_sem.post();
			m_size++;

			if (f) f();
        }


        std::shared_ptr<T> pop() {
            m_sem.wait();

            std::lock_guard<std::mutex> lock(m_mutex);

            auto msg = m_queue.front();
            m_queue.pop();
			m_size--;
            return msg;
        }

        std::shared_ptr<T> trypop(bool & bSuccess) {
            bSuccess = false;

            if (m_sem.trywait()) {
                std::unique_lock<std::mutex> lock(m_mutex);

                auto msg = m_queue.front();
                m_queue.pop();
                bSuccess = true;

				m_size--;
                return msg;
            }

            return std::shared_ptr<T>(nullptr);
        }

		size_t size() { return m_size; }

    private:
        CSemaphore m_sem;
        std::mutex m_mutex;
        std::queue<std::shared_ptr<T>> m_queue;
		uint64_t m_size = 0;
    };

#ifdef NLOHMANN
    class CJsonQueue {
    public:
        CJsonQueue() {
        }

        void push(json msg) {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_queue.push(msg);
            m_sem.post();
        }

        void push(json msg, std::function<void()> f) {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_queue.push(msg);
            m_sem.post();

			if (f) f();
        }

        json pop() {
            m_sem.wait();

            std::lock_guard<std::mutex> lock(m_mutex);

            auto msg = m_queue.front();
            m_queue.pop();

            return msg;
        }

        json trypop(bool & bSuccess) {
            bSuccess = false;

            if (m_sem.trywait()) {
                std::unique_lock<std::mutex> lock(m_mutex);

                auto msg = m_queue.front();
                m_queue.pop();
                bSuccess = true;

                return msg;
            }

            return json();
        }

    private:
        CSemaphore m_sem;
        std::mutex m_mutex;
        std::queue<json> m_queue;
    };
#endif

    template <typename T>
    class CLoopQueue {
    public:
        CLoopQueue(size_t max) : _max(max) {
            _b = new T*[max];
        }

        ~CLoopQueue() {
            delete [] _b;
        }

        void push(T * msg) {
            while (_h == ((_t + 1) % _max)) {
                msp(1);
            }

            _b[_t] = msg;
            _t = (_t + 1) % _max;
        }

        T * pop() {
            while (_h == _t) {
                msp(1);
            }

            T * p = _b[_h];
            _h = (_h + 1) % _max;

            return p;
        }

    private:
        T ** _b = nullptr;
        size_t _max = 0;
        size_t _h = 0;
        size_t _t = 0;
    };

    class CQueue {
	public:
		CQueue() {
		}

        void push(void * msg) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_queue.push(msg);
			m_sem.post();
		}

        void * pop() {
			m_sem.wait();

            std::unique_lock<std::mutex> lock(m_mutex);
            void * msg = m_queue.front();
			m_queue.pop();

			return msg;
		}

        void * trypop(bool & bSuccess) {
            bSuccess = false;

            if (m_sem.trywait()) {
                std::unique_lock<std::mutex> lock(m_mutex);
                void * msg = m_queue.front();
                m_queue.pop();
                bSuccess = true;

                return msg;
            }

            return NULL;
        }

    private:
		CSemaphore m_sem;
		std::mutex m_mutex;
        std::queue<void*> m_queue;
	};
//}

//{ 创建一个线程
	template <typename T, typename ...A>
    std::thread createThread(T && f, A && ... a) {
		std::thread t(std::forward<T>(f), std::forward<A>(a)...);
		t.detach();
        return t;
	}
//}

//{ index 序号
	template <typename T>
	class CIndex {
		struct node {
			node(T _i) { i = _i; n = NULL; }
			T i;
			struct node *n;
		};
		typedef node list;
		public:
            static_assert(std::is_arithmetic<T>::value, "Not Support");
			CIndex() {
				h = NULL;
				value = 0;
			}

			virtual ~CIndex() {
				while (h != NULL) {
					node *n = h;
					h = h->n;
					delete n;
				}
			}

			T pop() {
				if (h) {
					node *t = h;
					T _i = h->i;
					h = h->n;
					delete t;
					return _i;
				}
				return value++;
			}

			void push(T _i) {
				if (_i == value-1) {
					value--;
					return ;
				}
				node *t = new node(_i);
				if (!h) {
					h = t;
				} else {
					if (t->i < h->i) {
						t->n = h;
						h = t;
					} else {
						node *k = h;
						while(k->n) {
							if (t->i < k->n->i) {
								t->n = k->n;
								k->n = t;
								break;
							}
							k = k->n;
						}
						if (!k->n)
							k->n = t;
					}
				}
			}

            void clear() {
                while (h != NULL) {
                    node *n = h;
                    h = h->n;
                    delete n;
                }
                h = nullptr;
                value = 0;
            }
		private:
			struct node *h;
			T value;
	};
//}

//{ 环形内存
	class CPingPong {
	public:
		CPingPong(size_t size, bool bLock = false) : m_lock(bLock) {
			m_msg = (char*)malloc(size);
            if (nullptr == m_msg) throw std::bad_alloc();

			memset(m_msg, 0, size);

			m_size = size;
			m_wLen = size;
		}

        CPingPong(char * buf, size_t size, size_t already, bool bLock = false) : m_lock(bLock) {
            if (already > size) throw std::bad_alloc();

            m_msg = buf;
            if (nullptr == m_msg) throw std::bad_alloc();

            m_size = size;
            m_wLen = size;

            m_rLen += already;
            m_wLen -= already;
            m_wPos += already;
            m_wPos %= m_size;
        }

		~CPingPong() {
			free(m_msg);
		}

		bool push(const char* msg, size_t size) {
			std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);

			if (m_lock) {
				lock.lock();
			}

			if (size > m_wLen) {
				if (m_lock) {
					lock.unlock();
				}
				return false;
			}

			if (m_wPos + size > m_size) {
				size_t u32L1 = m_size - m_wPos;
				size_t u32L2 = size - u32L1;
				memcpy(m_msg + m_wPos, msg, u32L1);
				memcpy(m_msg, msg + u32L1, u32L2);
			}
			else {
				memcpy(m_msg + m_wPos, msg, size);
			}

			m_rLen += size;
			m_wLen -= size;
			m_wPos += size;
            m_wPos %= m_size;

			if (m_lock) {
				lock.unlock();
			}

			return true;
		}

		bool push(const char* msg) {
			return push(msg, strlen(msg));
		}

		bool pop(char* msg, size_t size) {
			std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);

			if (m_lock) {
				lock.lock();
			}

			if (size > m_rLen) {
				if (m_lock) {
					lock.unlock();
				}
				return false;
			}

			if (m_rPos + size > m_size) {
				size_t u32L1 = m_size - m_rPos;
				size_t u32L2 = size - u32L1;
				memcpy(msg, m_msg + m_rPos, u32L1);
				memcpy(msg + u32L1, m_msg, u32L2);
			}
			else {
				memcpy(msg, m_msg + m_rPos, size);
			}

			m_rPos += size;
			m_rPos %= m_size;

			m_rLen -= size;
			m_wLen += size;

			if (m_lock) {
				lock.unlock();
			}

			return true;
		}

		bool message(char* msg, size_t size) {
			std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);

			if (m_lock) {
				lock.lock();
			}

			if (size > m_rLen) {
				if (m_lock) {
					lock.unlock();
				}
				return false;
			}

			if (m_rPos + size > m_size) {
				size_t u32L1 = m_size - m_rPos;
				size_t u32L2 = size - u32L1;
				memcpy(msg, m_msg + m_rPos, u32L1);
				memcpy(msg + u32L1, m_msg, u32L2);
			}
			else {
				memcpy(msg, m_msg + m_rPos, size);
			}

			if (m_lock) {
				lock.unlock();
			}

			return true;
		}

		size_t readable() {
			std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);

			if (m_lock) {
				lock.lock();
			}

			size_t s = m_rLen;

			if (m_lock) {
				lock.unlock();
			}

			return s;
		}

		size_t writeable() {
			std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);

			if (m_lock) {
				lock.lock();
			}

			size_t s = m_wLen;

			if (m_lock) {
				lock.unlock();
			}

			return s;
		}

		size_t size() {
			return m_size;
		}

		void clear() {
			std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);

			if (m_lock) {
				lock.lock();
			}

			m_rLen = 0;
			m_wLen = m_size;
			m_rPos = 0;
			m_wPos = 0;

			if (m_lock) {
				lock.unlock();
			}
		}

	private:
		std::mutex m_mutex;
		bool m_lock = false;
		char* m_msg = nullptr;
		size_t m_size = 0;
		size_t m_rLen = 0;
		size_t m_wLen = 0;
		size_t m_rPos = 0;
		size_t m_wPos = 0;
	};
//}

//{
	// 在 string 的基础上增加了隐式类型转换
	struct variant : public std::string {
		template<typename T>
		variant(const T& t) :
            std::string(std::to_string(t)) {
		}
		template<size_t N>
		variant(const char(&s)[N]) :
			std::string(s, N) {
		}
		variant(const char* cstr) :
			std::string(cstr) {
		}
		variant(const std::string& other = std::string()) :
			std::string(other) {
		}
		template<typename T>
		operator T() const {
			T t;
			std::stringstream ss;
			return ss << *this && ss >> t ? t : T();
		}
		template<typename T> bool operator ==(const T& t) const {
			return 0 == this->compare(variant(t));
		}
		bool operator ==(const char* t) const {
			return this->compare(t) == 0;
		}
		template<typename T>
		T as() const {
			return (T)(*this);
		}
	};
//}

//{
    template <typename T>
    std::string stream(std::vector<T> v) {
        if (v.size() == 0) return "{}";

        std::stringstream o;

        o << "{";

        size_t size = v.size();
        for (size_t i=0; i<size-1; i++) {
            o << v[i] << ",";
        }

        o << v[size-1] << "}";

        return o.str();
    }
//}

//{ 临时 T * 内存分配
    template <typename T = char>
    inline std::shared_ptr<T> getBuffer(size_t size)
    {
        std::shared_ptr<T> p(new T [size], [](T *pb) {
            delete [] pb;
        });

        return p;
    }

    class Stream {
    public:
        Stream(uint8_t * stream, uint32_t size) { m_pStream = new uint8_t[size]; memcpy(m_pStream, stream, size); m_size = size; }
        Stream(uint32_t size) { m_pStream = new uint8_t[size]; m_size = size; }
        ~Stream() { delete m_pStream; }
        uint8_t * data() { return m_pStream; }
        uint32_t size() { return m_size; }
    private:
        uint8_t * m_pStream = nullptr; uint32_t m_size = 0;
    };

    inline std::shared_ptr<Stream> getStream(uint8_t * stream, uint32_t size) {
        std::shared_ptr<Stream> sp(new Stream(stream, size));
        return sp;
    }

    inline std::shared_ptr<Stream> getStream(uint32_t size) {
        std::shared_ptr<Stream> sp(new Stream(size));
        return sp;
    }
//}

//{ set name of thread
    inline void setThreadName(const char *name)
    {
        pthread_setname_np(pthread_self(), name);
    }
//}

//{
    // 不应该这么做，最开始就应该使用带符号类型，然而我不想去改库了
    template <typename T>
    inline bool invalid(T v)
    {
        if (((T)-1) == v) return true;
        return false;
    }
//}

inline std::vector<std::string> stringSplit(const std::string & s, const std::string delim=",")
{
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len)
    {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0)
        {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

inline std::string stringFilename(std::string path)
{
    size_t pos = path.rfind('/');
    if (pos == std::string::npos) return path;
    return path.substr(pos+1);
}

inline std::string getFileExt(std::string &strFile, int isLower=0)
{
    if(isLower == 1)
    {
        std::string strTemp = strFile;
        std::transform(strTemp.begin(), strTemp.end(), strTemp.begin(), ::tolower);
        std::string::size_type pos = strTemp.rfind('.');
        std::string strExt = strTemp.substr(pos == std::string::npos ? strTemp.length() : pos+1);
        return strExt;
    }
    else
    {
        std::string::size_type pos = strFile.rfind('.');
        std::string strExt = strFile.substr(pos == std::string::npos ? strFile.length() : pos+1);
        return strExt;
    }
}

#ifdef NLOHMANN
class CThreadPoll {
    using Func = std::function<void(json)>;
public:
    static CThreadPoll & instance() {
        static CThreadPoll instance[4];
        static std::atomic<uint32_t> id{0};

        return instance[id++%4];
    }

    void push(std::function<void(json)> f, json j) {
        if (!f) return ;

        std::shared_ptr<json> sj = std::make_shared<json>();
        *sj = j;
        m_queueJson.push(sj);

        std::shared_ptr<Func> sf = std::make_shared<Func>();
        *sf = f;
        m_queueFunc.push(sf);
    }

    ~CThreadPoll() {
        m_queueJson.push(nullptr);
        m_queueFunc.push(nullptr);
    }

private:
    CThreadPoll() {
        createThread([this]() {
            while (true) {
                auto f = m_queueFunc.pop();
                auto j = m_queueJson.pop();

                if (!f || !j) break;

                (*f)(*j);
            }
        });
    }

private:
    CShpQueue<json> m_queueJson;
    CShpQueue<Func> m_queueFunc;
};
#endif

#ifdef SPDLOG
template<typename T>
void show(T & t) {
	for (auto & it : t) {
		SPDLOG_INFO("{} {}", it.first, it.second);
	}
}
#endif

#endif
