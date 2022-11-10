// ----------------------------------------------------------------------------
//
// Logger to store data in a file with no dynamic allocation after construction
//

#ifndef TLGR_HPP_
#define TLGR_HPP_

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <string>

namespace tlgr
{
class Tlgr
{
  public:
    Tlgr(const std::string & file_name) : log_file_name_(file_name) {}

    virtual ~Tlgr()
    {
        if (log_file_fp_ != nullptr)
        {
            std::fflush(log_file_fp_);
            std::fclose(log_file_fp_);
        }
    }

    bool init()
    {
        if (log_file_fp_ != nullptr)
        {
            return false;
        }

        log_file_fp_ = std::fopen(log_file_name_.c_str(), "a+");
        if (!log_file_fp_)
        {
            return false;
        }

        fprintf(log_file_fp_, "----\n");
        return true;
    }

    const std::string & GetLogFileName() const { return log_file_name_; }

    // ------------------------------------------------------------------------
    Tlgr & timestamp()
    {
        log_timestamp();
        return *this;
    }

    Tlgr & endl()
    {
        fprintf(log_file_fp_, "\n");
        std::fflush(log_file_fp_);
        return *this;
    }

    Tlgr & log(uint32_t data)
    {
        fprintf(log_file_fp_, " %d", data);
        return *this;
    }

    Tlgr & log(const char * data)
    {
        fprintf(log_file_fp_, " %s", data);
        return *this;
    }

    Tlgr & log(const uint8_t * data, const size_t len)
    {
        if (len > 0)
        {
            for (uint8_t i = 0; i < len; ++i)
            {
                fprintf(log_file_fp_, "%02X,", data[i]);
            }
        }
        return *this;
    }

    template <class InputIt>
    Tlgr & log(InputIt begin, InputIt end)
    {
        while (begin != end)
        {
            fprintf(log_file_fp_, "%02X,", *begin);
            begin++;
        }
        return *this;
    }

  private:
    bool log_timestamp()
    {
        using namespace std::chrono;
        milliseconds ms{duration_cast<milliseconds>(system_clock::now().time_since_epoch())};

        fprintf(log_file_fp_, "%llu", static_cast<long long unsigned int>(ms.count()));
        return true;
    }

    const std::string log_file_name_{};

    FILE * log_file_fp_{nullptr};
};

}  // namespace tlgr

#endif  // TLGR_HPP_