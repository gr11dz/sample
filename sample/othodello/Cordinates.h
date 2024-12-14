using namespace std;
class Cordinates{
    private:
        int x;
        int y;
    public:
        Cordinates() : x(0) , y(0){}
        Cordinates(int x , int y) : x(x) , y(y){}
        void set_x(int x){
            this->x = x;
        }
        void set_y(int y){
            this->y = y;
        }
        int get_x(){
            return x;
        }
        int get_y(){
            return y;
        }
        Cordinates operator+(Cordinates const& obj1){
            Cordinates result(x + obj1.x , y + obj1.y);
            return result;
        }
        Cordinates operator-(Cordinates const& obj1){
            Cordinates result(x - obj1.x , y - obj1.y);
            return result;
        }
};
