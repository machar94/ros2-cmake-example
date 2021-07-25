#include "math/math.hpp"
#include "rclcpp/rclcpp.hpp"

class MathNode : public rclcpp::Node
{
public:
    MathNode() : Node("math_node")
    {
        int num1 = 5;
        int num2 = 7;
        RCLCPP_INFO(this->get_logger(), "%d + %d = %d", num1, num2, add_two(5, 7));
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MathNode>());
    rclcpp::shutdown();
}