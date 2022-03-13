# Better cin

Cpp library for inputs with a place holder that may help the user do the cin

```cpp
#include <iostream>
#include <string>
#include <vector>

#include "main.h"

int main() {
	std::vector<std::vector<std::string>> templates = { {"cd", "root", "test"}, {"other", "choice"}, {"option", "/s"} };
	std::vector<std::string> template1 = {"cd", "root", "test", "other", "choice", "option", "/s"};
	std::string output;
	bcin(output, " >", templates);
	std::cout << output << std::endl;
	bcin(output, " >", template1);
	std::cout << output;
}
```

#### After the first character typed a help is show
![image](https://user-images.githubusercontent.com/73474137/152681372-8c5adedc-e1c9-40fb-9b2b-c63c9db5f25b.png)

#### If the choice is the word you want you can just hit the tabulation button
![image](https://user-images.githubusercontent.com/73474137/152681386-96d74241-25af-4d81-9502-1e3bf58652a1.png)

#### If the choice is not the thing you want type the first letter and it will return a new suggestion 
![image](https://user-images.githubusercontent.com/73474137/152681405-756465b2-8451-4021-8c58-bf55b9f931e6.png)
