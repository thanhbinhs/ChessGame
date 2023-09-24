#include <SFML/Graphics.hpp>
// chế độ cầu hòa
int main()
{

    // Tạo nút cầu hòa
    sf::RectangleShape button(sf::Vector2f(100, 50));
    button.setPosition(350, 500);
    button.setFillColor(sf::Color::Green);

    // Tạo văn bản cầu hòa
    sf::Font font;
    if (!font.loadFromFile("../Data/Font/font_1.ttf"))
    {
        // Xử lý lỗi tải font
        return -1;
    }
    sf::Text text("Cầu hòa", font, 24);
    text.setPosition(365, 515);
    text.setFillColor(sf::Color::Black);

    // Vòng lặp chính
    while (window.isOpen())
    {
        // Xử lý các sự kiện trong vòng lặp
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Đóng cửa sổ khi nhấn nút đóng hoặc phím ESC
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();

            // Xử lý sự kiện chuột
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Lấy tọa độ chuột
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                // Kiểm tra xem có click vào nút cầu hòa không
                if (x >= 350 && x < 450 && y >= 500 && y < 550)
                {
                    // Hiển thị văn bản "Cầu hòa"
                    window.draw(text);
                }
            }
        }

        // Vẽ các đối tượng lên cửa sổ đồ họa
        window.clear();
        window.draw(button);
        window.display();
    }

    return 0;
}

