#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>

class CircularBuffer {
  public:
    CircularBuffer(uint8_t* buf, size_t capacity) : buffer(buf), kCapacity(capacity) {
      head_index = 0;
      tail_index = 0;
      count = 0;
    }

    bool push(uint8_t byte) {
        if (count == kCapacity) {
          return false;
        }
        count++;
        if (head_index < kCapacity) {
          buffer[head_index++] = byte;
        } else {
          head_index = 0;
          buffer[head_index++] = byte;
        }

        return true;
    }

    bool pop(uint8_t& out) {
        if (count == 0) {
          return false;
        }
        count--;
        if (tail_index < kCapacity) {
          out = buffer[tail_index++];
        } else {
          tail_index = 0;
          out = buffer[tail_index++];
        }
        return true;
    }

    bool isEmpty() const {
      if (count == 0) {
        return true;
      }
      return false;
    }

    bool isFull() const {
      if (count == kCapacity) {
        return true;
      }
      return false;
    }

    // Elements are in the buffer
    size_t size() const {
        return count;
    }

  private:
    size_t head_index;
    size_t tail_index;
    size_t count;
    uint8_t * buffer;
    const size_t kCapacity;
};

// Test code - you can modify this
int main() {
    const size_t buffer_size{8};
    uint8_t backing_buffer[8];
    CircularBuffer buffer(backing_buffer, 8);

    // Add your test cases here
    std::cout << buffer.isEmpty() << ":" << buffer.isFull() << std::endl;

    uint8_t value{0};
    std::cout << buffer.pop(value) << std::endl;
    std::cout << buffer.push(42) << std::endl;
    auto result = buffer.pop(value);

    std::cout << result << ":" << static_cast<uint32_t>(value) << std::endl;

    for (uint8_t i=0; i<10; i++) {
      auto result = buffer.push(i*10);

      if (i >= buffer_size) {
        std::cout << result << " Expect 0" << std::endl;
      }
    }

    std::cout << buffer.isFull() << " Expect 1" << std::endl;

    for (uint8_t i=0; i<10; i++) {
      uint8_t val{0};
      auto result = buffer.pop(val);

      if (i >= buffer_size) {
        std::cout << result << " Expect 0" << std::endl;
      } else {
        std::cout << static_cast<uint32_t>(val) << " Expect: " << static_cast<uint32_t>(i*10) << std::endl;
      }
    }

    return 0;
}
