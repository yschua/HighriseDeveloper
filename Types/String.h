#include <string>
#include <sstream>

template <class T>
std::string ToString(T Other) {
   std::ostringstream s;
   s << Other;
   return s.str();
}

int ToInt(std::string Other) {
   std::istringstream s(Other);
   int To;
   s >> To;
   return To;
}

template <class T>
T FromString(std::string Other) {
   std::istringstream s(Other);
   T To;
   s >> To;
   return To;
}
