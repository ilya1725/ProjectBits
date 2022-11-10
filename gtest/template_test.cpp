//
//  Google test how to test templated classes
//

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <type_traits>

// The actual class to run the test on
template <std::size_t N>
class Line {
  public:
    explicit Line(){};

    std::size_t length() const {
        return length_;
    }

  private:
    static constexpr std::size_t length_{N};
};

template <typename T>
class line_tester : public ::testing::Test
{
  protected:
    static const size_t kRedundantCmdNum{3};

    line_tester() {}

    void SetUp()
    {
        // code here will execute just before the test ensues
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    virtual ~line_tester() {}

    typename T::value_type GetLineLength() { return line_.length();}

  private:
    Line<T::value> line_{};
};

using test_types = ::testing::Types<
    std::integral_constant<std::size_t,2>,
    std::integral_constant<std::size_t,3>,
    std::integral_constant<std::size_t,5>>;

TYPED_TEST_CASE(line_tester, test_types);

TYPED_TEST(line_tester, get_capacity) {
    static constexpr std::size_t n = TypeParam::value;
    ASSERT_EQ(n, this->GetLineLength());
}
