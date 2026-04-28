struct Port {
    int port;
    explicit Port(int port) : port(port) {}
};

void connection (Port p) {

}

#include<vector>

int main () {
    std::vector <int> v;
    int* p = new int();

    int * p2 = static_cast<int*>(operator new(4));
    new (p2) int();
char buff[4];
new (buff) int();

    Port p (8000.0);
    connection(Port{8080});
}