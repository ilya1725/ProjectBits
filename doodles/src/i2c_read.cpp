/*
 * ============================================================================
 *  Embedded Coding Exercise — Rolling-Average Temperature Publisher (C++)
 * ============================================================================
 *
 *  You are integrating the "TMP-1000" temperature sensor on a bare-metal MCU.
 *
 *  Sensor datasheet excerpt:
 *    - Internal sample rate: 1000 Hz.
 *    - Interface: I2C, 7-bit address 0x48.
 *    - Register map (registers auto-increment during a burst read):
 *        0x00  TEMP_MSB   upper 8 bits of the latest 16-bit sample
 *        0x01  TEMP_LSB   lower 8 bits
 *      The sample is a signed 16-bit two's-complement value.
 *      A single 2-byte burst read starting at 0x00 returns one coherent
 *      sample. Two separate 1-byte reads are NOT guaranteed to come from
 *      the same sample. Reading TEMP_LSB clears the data-ready condition.
 *    - Scale: 1 LSB = 0.03125 degC  (degC = raw / 32.0).
 *    - Valid operating range: -50 degC to +750 degC. Values outside this
 *      range indicate a sensor fault.
 *    - DRDY: the sensor drives PIN2 high (rising edge) each time a new
 *      sample becomes available.
 *
 *  Task:
 *    Publish, at 10 Hz over the UART, the rolling average of the sensor
 *    samples from the last 250 ms, as an ASCII line such as:
 *        "T=23.41\n"
 *    The publish rate must not drift over time.
 *
 *  Notes:
 *    - Target is a small MCU: be deliberate about memory, ISR duration,
 *      and what runs in interrupt vs. main context.
 *    - You may use the standard library.
 *    - State any assumptions you make about the HAL semantics.
 *    - Think out loud about edge cases; handling or explicitly documenting
 *      them counts.
 *
 * ============================================================================
 *  Provided HAL (already implemented — do not modify, just use it)
 * ============================================================================
 */
#include <cstdint>
#include <cstddef>

#include <queue>
#include <atomic>

 
enum PinName { PIN2, I2C_SDA, I2C_SCL, USBTX, USBRX };
 
// Monotonic millisecond tick since boot. Wraps around at 2^32.
uint32_t millis();
 
// Globally disable / enable interrupts (for critical sections).
void __disable_irq();
void __enable_irq();
 
class I2C {
public:
  	const int TEMP_MSB{0x0};
  	const int TEMP_LSB{0x1};
  	const float conversion_scale{32.0};
  
    I2C(PinName sda, PinName scl);
  
  	bool Init() {      
      return true;
    }
    // Both return 0 on success, non-zero on NACK / bus error.
    // repeated=true ends the transfer without a STOP so the next
    // transfer begins with a repeated START.
    int write(int address_7bit, const char* data, int length, bool repeated = false);
    int read(int address_7bit, char* data, int length, bool repeated = false);

  	float GetAvg();
  	// To be called in the intterupt handler
    void read_data() {
    	// TODO: handle failures
      
      uint16_t raw_data{0};
      {
      	char data{0};
      	const auto res = read(TEMP_MSB, &data, 1, false);      
        raw_data = (static_cast<uint16_t>(data) << 8);
      }
      {
      	char data{0};
      	const auto res = read(TEMP_MSB, &data, 1, false);      
        raw_data = (raw_data & static_cast<uint16_t>(data));
      }
      
      // convert to float
      const float real_data = static_cast<float)(raw_data) / conversion_scale;
      
      // TODO: make sure the API doesn't allocate.
      // avg = (x1 + x2 + ... xn) / n
      // avg+1 = ((avg * n) + xn+1) / n+1
      // 
      if (data_.full()) {
        data_.pop_front();
      }
      data_.push_back(real_data);
  	}

private:
  std::atomic<float> avg_data_{0.0f};
};
 
class Serial {
public:
    Serial(PinName tx, PinName rx, int baud = 115200);
    // Blocking write; returns bytes written or negative on error.
    long write(const void* buffer, size_t length);
};
 
class InterruptIn {
public:
    explicit InterruptIn(PinName pin, std::function<void ()> callback) : pin_(pin), callback_(callback) {};
    void rise(void (*callback)());   // callback runs in interrupt context
    void enable_irq();
    void disable_irq();
  
private:
  std::atomic<uint16_t> raw_temperature_{};
  std::function<> callback_;
  const PinName pin_;
};
 
/*
 * ============================================================================
 *  Your implementation starts here.
 * ============================================================================
 */
 
int main() {
    I2C i2c(I2C_SDA, I2C_SCL);
  	if (i2c.Init() == false) {
      return 1;
    }
  
    Serial serial(USBTX, USBRX);
  
  	// TODO: check the function pointer syntax
    InterruptIn drdy(PIN2, i2c.read_data());
  	drdy.enable_irq();
 
    // TODO: implement.
  	// Interrupt on PIN2 when data is ready.
  	// Read the data, put in the queue.
  	// Write at 10Hz.
 
  	std::string uart_buffer{132};
  
    for (;;) {
        // TODO
      	// read mills();
      	// If mod 100ms - use std::format() to format into uart_buffer, then serial.write(uart_buffer.data(), uart_buffer.size())
    }
  
  	return 0;
}
