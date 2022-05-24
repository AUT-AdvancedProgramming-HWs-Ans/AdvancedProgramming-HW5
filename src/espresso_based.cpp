#include "espresso_based.h"

EspressoBased::EspressoBased()
    : name { "EspressoBased" }
    , ingredients {}
{

    /**
     * @brief Default constructor
     */
}

EspressoBased::EspressoBased(const EspressoBased& esp)
    : name { esp.name }
    , ingredients {}
{

    /**
     * @brief Copy constructor
     *
     * @param esp
     */

    for (const auto& i : esp.ingredients) {

#define INGREDIENTS(Name)       \
    if (i->get_name() == #Name) \
        ingredients.push_back(new Name { i->get_units() });

        INGREDIENTS(Cinnamon);
        INGREDIENTS(Chocolate);
        INGREDIENTS(Sugar);
        INGREDIENTS(Cookie);
        INGREDIENTS(Espresso);
        INGREDIENTS(Milk);
        INGREDIENTS(MilkFoam);
        INGREDIENTS(Water);
    }
}

EspressoBased::~EspressoBased()
{
    /**
     * @brief Destructor
     */
    for (const auto& i : ingredients)
        delete i;
    ingredients.clear();
}

void EspressoBased::operator=(const EspressoBased& esp)
{
    /**
     * @brief Assignment operator
     *
     * @param esp
     */
    if (this != &esp) {
        name = esp.name;

        for (auto& i : ingredients)
            delete i;
        ingredients.clear();

        for (const auto& i : esp.ingredients) {

#define INGREDIENTS(Name)       \
    if (i->get_name() == #Name) \
        ingredients.push_back(new Name { i->get_units() });

            INGREDIENTS(Cinnamon);
            INGREDIENTS(Chocolate);
            INGREDIENTS(Sugar);
            INGREDIENTS(Cookie);
            INGREDIENTS(Espresso);
            INGREDIENTS(Milk);
            INGREDIENTS(MilkFoam);
            INGREDIENTS(Water);
        }
    }
}

std::vector<Ingredient*>& EspressoBased::get_ingredients()
{
    /**
     * @brief Getter for ingredients
     *
     * @return std::vector<Ingredient*>&
     */
    return ingredients;
}

void EspressoBased::brew()
{
    /**
     * @brief Brews the coffee
     */

    // Defining namespace for suffixes for duration literals
    using namespace std::chrono_literals;

    // Initial Message
    // Setting the properties of the initial message
    auto initial_process { ftxui::vbox({ ftxui::text(" Please Wait! Your "
                                             + this->get_name()
                                             + " is brewing :")
            | ftxui::borderHeavy
            | ftxui::color(ftxui::Color::Cyan),
        ftxui::text("Loading...\n")
            | ftxui::color(ftxui::Color::RGB(120, 120, 50)) }) };

    // Creating the screen of the initial message
    auto initial_screen { ftxui::Screen::Create(ftxui::Dimension::Fit(initial_process),
        ftxui::Dimension::Fit(initial_process)) };

    ftxui::Render(initial_screen, initial_process);
    initial_screen.Print();

    std::cout << std::endl;

    std::this_thread::sleep_for(1s);

    // Initialize the brewing process

    // Defining the variables

    size_t indexOfIngredient {};

    size_t sumOfUnits {};
    for (auto components : ingredients)
        sumOfUnits += components->get_units();

    ftxui::Elements cap_ingredients {};
    size_t numberOfAddedUnits { ingredients[indexOfIngredient]->get_units() };

    std::string reset_position {};

    std::map<std::string, ftxui::Color> colorOfIngredients { { "Cinnamon",
                                                                 ftxui::Color::RGB(210, 105, 30) },
        { "Chocolate",
            ftxui::Color::RGB(123, 63, 0) },
        { "Sugar",
            ftxui::Color::RGB(240, 240, 236) },
        { "Cookie",
            ftxui::Color::RGB(230, 206, 160) },
        { "Espresso",
            ftxui::Color::RGB(60, 34, 24) },
        { "Milk",
            ftxui::Color::RGB(253, 255, 246) },
        { "MilkFoam",
            ftxui::Color::RGB(255, 238, 204) },
        { "Water",
            ftxui::Color::RGB(212, 241, 249) } };

    for (float prcnt {}; prcnt <= 1.01f; prcnt += 0.01f) {

        std::string prcnt_brewed { std::to_string(int(prcnt * 100)) + "/100" };

        // Update the brewing process
        if (static_cast<size_t>(prcnt * 100)
            == static_cast<size_t>(numberOfAddedUnits * 100 / sumOfUnits)) {
            cap_ingredients.insert(cap_ingredients.begin(),
                ftxui::text(
                    ingredients[indexOfIngredient]->get_name()
                    + " : " + std::to_string(ingredients[indexOfIngredient]->get_units())
                    + "/" + std::to_string(sumOfUnits))
                    | ftxui::color(ftxui::Color::Black)
                    | ftxui::borderDouble
                    | ftxui::bgcolor(colorOfIngredients[ingredients[indexOfIngredient]
                                                            ->get_name()]));

            indexOfIngredient++;
            numberOfAddedUnits += ingredients[indexOfIngredient]->get_units();
        }

        if (cap_ingredients.empty()) {

            // Don't show the ingredients boxs if the cap_ingredients is empty

            // Setting the properties of brewing process
            auto brewing_process { ftxui::hbox({ ftxui::text("Brewing... ")
                    | ftxui::color(ftxui::Color::Green),
                ftxui::gauge(prcnt)
                    | ftxui::flex
                    | ftxui::color(ftxui::Color::Red),
                ftxui::text(" " + prcnt_brewed)
                    | ftxui::color(ftxui::Color::BlueLight) }) };

            // Creating the screen of the brewing process
            auto brewing_screen { ftxui::Screen::Create(
                ftxui::Dimension::Full(),
                ftxui::Dimension::Fit(brewing_process)) };

            ftxui::Render(brewing_screen, brewing_process);
            std::cout << reset_position;
            brewing_screen.Print();
            reset_position = brewing_screen.ResetPosition();

        }

        else {

            // Setting the properties of brewing process
            auto brewing_process { ftxui::hbox({ ftxui::text("Brewing... ")
                    | ftxui::color(ftxui::Color::Green),
                ftxui::gauge(prcnt)
                    | ftxui::flex
                    | ftxui::color(ftxui::Color::Red),
                ftxui::text(" " + prcnt_brewed)
                    | ftxui::color(ftxui::Color::BlueLight),
                ftxui::vbox(cap_ingredients)
                    | ftxui::borderRounded
                    | ftxui::color(ftxui::Color::RGB(165, 42, 42)) }) };

            // Creating the screen of the brewing process
            auto brewing_screen { ftxui::Screen::Create(
                ftxui::Dimension::Full(),
                ftxui::Dimension::Fit(brewing_process)) };

            ftxui::Render(brewing_screen, brewing_process);
            std::cout << reset_position;
            brewing_screen.Print();
            reset_position = brewing_screen.ResetPosition();
        }

        std::this_thread::sleep_for(0.1s);
    }
    std::cout << std::endl;

    // Final message

    // Setting the properties of the final message
    auto final_message { ftxui::vbox({ ftxui::text(" Your " + this->get_name() + " is ready!!! ")
        | ftxui::borderDouble
        | ftxui::color(ftxui::Color::Green) }) };

    // Creating the screen of the final message
    auto final_screen { ftxui::Screen::Create(ftxui::Dimension::Fit(final_message),
        ftxui::Dimension::Fit(final_message)) };

    ftxui::Render(final_screen, final_message);
    final_screen.Print();

    std::cout << std::endl;
}