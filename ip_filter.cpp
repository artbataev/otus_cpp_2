#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string& str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

using IP_ADDRESS = std::vector<int>;
using IP_POOL = std::vector<IP_ADDRESS>;

std::ostream& operator<<(std::ostream& stream, const IP_ADDRESS& ip) {
    for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
        if (ip_part != ip.cbegin()) {
            stream << ".";

        }
        stream << *ip_part;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const IP_POOL& ip_pool) {
    for (const auto& ip:ip_pool) {
        stream << ip << std::endl;
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, IP_POOL& ip_pool) {
    for (std::string line; std::getline(stream, line);) {
        std::vector<std::string> v = split(line, '\t');
        auto current_ip_str = split(v.at(0), '.');
        IP_ADDRESS current_ip(current_ip_str.size());
        std::transform(current_ip_str.begin(), current_ip_str.end(), current_ip.begin(), [](std::string ip) {
            return std::stoi(ip);
        });
        if (current_ip.size() != 4) {
            throw std::logic_error("incorrect ip " + line);
        }
        ip_pool.push_back(current_ip);
    }
    return stream;
}


int main(int argc, char const *argv[]) {
    try {

        IP_POOL ip_pool;
//        std::fstream from("../data/ip_filter.tsv");
//        from >> ip_pool;
        std::cin >> ip_pool;

        // reverse lexicographically sort
        std::sort(ip_pool.rbegin(), ip_pool.rend());
        std::cout << ip_pool;

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        auto filter = [ip_pool](const auto& value) {
            IP_POOL filtered_pool;
            for (const auto& ip:ip_pool) {
                if (ip[0] == value) {
                    filtered_pool.push_back(ip);
                }
            }
            return filtered_pool;
        };
        auto filtered_pool_1 = filter(1);
        std::cout << filtered_pool_1;

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        auto filter2 = [ip_pool](const auto& value1, const auto& value2) {
            IP_POOL filtered_pool;
            for (const auto& ip:ip_pool) {
                if (ip[0] == value1 && ip[1] == value2) {
                    filtered_pool.push_back(ip);
                }
            }
            return filtered_pool;
        };
        // ip = filter(46, 70)
        auto filtered_pool_2 = filter2(46, 70);
        std::cout << filtered_pool_2;

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        auto filter_any = [ip_pool](const auto& value) {
            IP_POOL filtered_pool;
            for (const auto& ip:ip_pool) {
                bool use = false;
                for (const auto& elem:ip) {
                    use |= (elem == value);
                }
                if (use) {
                    filtered_pool.push_back(ip);
                }
            }
            return filtered_pool;
        };
        // ip = filter_any(46)
        auto filtered_pool_3 = filter_any(46);
        std::cout << filtered_pool_3;


        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
