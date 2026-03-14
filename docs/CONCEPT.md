


class SceneManager{
    std::unordered_map<std::string, SceneObject>

    {"menu": SceneObject()}


    void update(){
        state = scene;

        if (state != state_manager){
            state_manager = state;
            
        }

    }


    void switchScene(){

    }




};





vao.render()



for 1000 - 10000
    vao.render()


vao.render(1000)



int main() {
    // 1️⃣ Открываем файл TTF и читаем в память
    std::ifstream file("assets/arial.ttf", std::ios::binary);
    if (!file) {
        std::cout << "Cannot open font file\n";
        return 1;
    }

    // читаем весь файл в вектор unsigned char
    std::vector<unsigned char> ttf_buffer((std::istreambuf_iterator<char>(file)),
                                           std::istreambuf_iterator<char>());
    file.close();

    // 2️⃣ Инициализация шрифта
    stbtt_fontinfo font;
    if (!stbtt_InitFont(&font, ttf_buffer.data(), 0)) {
        std::cout << "Failed to init font\n";
        return 1;
    }

    // 3️⃣ Устанавливаем размер шрифта в пикселях
    float pixel_height = 48.0f; // размер шрифта
    float scale = stbtt_ScaleForPixelHeight(&font, pixel_height);

    // 4️⃣ Получаем bitmap для конкретного символа
    int width, height, xoff, yoff;
    char c = 'A'; // символ
    unsigned char* bitmap = stbtt_GetCodepointBitmap(&font, 0, scale, c, &width, &height, &xoff, &yoff);

    // 5️⃣ Выводим информацию о символе
    std::cout << "Symbol: " << c << "\n";
    std::cout << "Bitmap width: " << width << "\n";
    std::cout << "Bitmap height: " << height << "\n";
    std::cout << "x offset: " << xoff << ", y offset: " << yoff << "\n";

    // 6️⃣ bitmap теперь unsigned char* с размером width*height
    // Можно использовать для OpenGL текстуры
    // Пример: glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);

    // 7️⃣ Освобождаем память bitmap
    stbtt_FreeBitmap(bitmap, nullptr);

    return 0;
}





scenes_declarataion.hpp

#SCENE MENU
#include <scene_declaration.hpp>

class Menu





float scale = std::min(windowWidth / spriteWidth, windowHeight / spriteHeight);
newWidth  = spriteWidth  * scale;
newHeight = spriteHeight * scale;

// Центрируем:
offsetX = (windowWidth  - newWidth) / 2;
offsetY = (windowHeight - newHeight) / 2;



float scale = std::max(windowWidth / spriteWidth, windowHeight / spriteHeight);
newWidth  = spriteWidth  * scale;
newHeight = spriteHeight * scale;

// Центрируем:
offsetX = (windowWidth  - newWidth) / 2;
offsetY = (windowHeight - newHeight) / 2;






Логика игры должны выглядит самим образом
игра начинается с intro сцены которым приветствуется заставкой

дальше показывается сцена menu с кнопками 1) play 2) settings 3) quit

quit -> выкидывает с игры
settings -> сцена настройек
play -> показывает следующие кнопки game_player_info 0 - 9 и выберает как начинать игру и все такое и после выбранного сразу идем играть

главное правилы игры выбераем не мышкой а специальными клавишами WASD QEZXC ESC SPACE Fn+F1

W|S - для переключения кнопки
C - выбрать

ESC - выход из игры данные сохраняются 
Fn+F1 - пауза/старт

WASD & QEZXC SPACE - Игровые



u0 = x / aw
v0 = y / ah

u1 = x+w / aw
v1 = y+h / ah


u0 = 128 / 1024 = 0.125
v0 = 256 / 1024 = 0.25

u1 = 192 / 1024 = 0.1875
v1 = 320 / 1024 = 0.3125










21 march

Animation duration c++
text and dynamic text

main-menu, intro, settings


std::vector<float>  vertices = {
                // positions       // uv_coords
                0.0f, 1.0f,       0.0f, 1.0f,
                1.0f, 1.0f,       1.0f, 1.0f,
                1.0f, 0.0f,       1.0f, 0.0f,
                0.0f, 0.0f,       0.0f, 0.0f

            };

            std::vector<unsigned int> indices = {
                0, 1, 2, 2, 3, 0
            };



Atlas -> spriteOffsets 

AtlasFont
type_font = 1 - DEFAULT 2-OVERWORLD 3-MESSAGEBOX 4-JAPANBOX 5-JAPANOVERWORLD 6-MARIOLUIGITIMEOUT





1) TILE-MAP


