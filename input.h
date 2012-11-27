#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

class input
{
    public:

        input();
        ~input();

        std::string* userName();
        std::string* userLocation();

    private:

        std::string name;
        std::string location;
};

#endif // INPUT_H_INCLUDED
