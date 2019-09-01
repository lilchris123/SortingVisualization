#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
//handle any events
void handleEvent(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed)
		{
			window.close();
			exit(1);
		}
	}
}
//draws text on the window
void drawText(sf::RenderWindow &window, const string str, sf::Vector2f position, const sf::Font &font)
{
	sf::Text cmpTxt;
	cmpTxt.setFont(font);
	cmpTxt.setString(str);
	cmpTxt.setPosition(position);
	cmpTxt.setFillColor(sf::Color::White);
	window.draw(cmpTxt);
}
// visual representation of the list
void visualize(vector<int> &list, sf::RenderWindow &window, const int HEIGHT, int comparisons,const sf::Font &font)
{
	window.clear();
	handleEvent(window);
	for (int i = 0; i < list.size(); i++)
	{
		sf::RectangleShape line;
		line.setPosition(sf::Vector2f(i, HEIGHT- list[i]));
		line.setSize(sf::Vector2f(1, list[i]));
		line.setFillColor(sf::Color::Blue);
		window.draw(line);
	}
	drawText(window, "# of comparisons: " + to_string(comparisons),sf::Vector2f(1,1),font);
	window.display();
}
//selection sort algorithm returns time taken to sort list
sf::Time selectionSort(vector<int> &list, sf::RenderWindow &window, const int HEIGHT, const sf::Font &font) {
	sf::Time total_time;
	sf::Clock clock;

	int minimum, comparisons=0;
	for (int i = 0; i < list.size()-1; i++)
	{
		minimum = i;
		for (int j = i + 1; j < list.size(); j++)
		{
			if (list[minimum] > list[j])
				minimum = j;
			comparisons++;
		}
		swap(list[minimum], list[i]);
		total_time += clock.getElapsedTime();
		visualize(list, window, HEIGHT, comparisons, font);
		clock.restart();
	}
	return total_time;
}
sf::Time bubbleSort(vector<int> &list, sf::RenderWindow& window, const int HEIGHT, const sf::Font &font)
{
	sf::Time total_time;
	int comparisons = 0;
	sf::Clock clock;
	bool isSorted = false;
	while(!isSorted)
	{
		isSorted = true;
		for (int j = 0, k = 1; k < list.size(); j++, k++)
		{
			if (list[j] > list[k])
			{
				swap(list[j], list[k]);
				isSorted = false;
			}
			comparisons++;
			total_time += clock.getElapsedTime();
			visualize(list, window, HEIGHT, comparisons, font);
			clock.restart();
		}
	}
	return total_time;
}
sf::Time insertionSort(vector<int> &list, sf::RenderWindow& window, const int HEIGHT, const sf::Font &font)
{
	sf::Time total_time;
	int comparisons = 0;
	sf::Clock clock;
	for(int i=0; i<list.size()-1; i++)
	{
		int j = i;
		while (j > 0 && list[j-1] > list[j])
		{
			swap(list[j], list[j-1]);
			j--;
			comparisons++;
			total_time += clock.getElapsedTime();
			visualize(list, window, HEIGHT, comparisons,font );
			clock.restart();
		}
	}
	return total_time;
}

//randomize list from 0 to height of the window
void initializeList(vector<int> &list,const int HEIGHT)
{
	srand(time(0));
	vector<int>::iterator it = list.begin();
	while (it != list.end())
	{
		*it=rand() % HEIGHT;
		it++;
	}
}
int main() {
	int WIDTH;
	int HEIGHT;
	short algo;
	cout << "Enter Width of Window (size of array): "<<endl;
	std::cin >> WIDTH;
	cout << "Enter Height of Window (distinct numbers ): " << endl;
	std::cin >> HEIGHT;
	cout << "Enter Algorithm: 1)Selection Sort 2)Bubble Sort 3)Insertion Sort " << endl;
	std::cin >> algo;
    
    sf::Font font;
    if (!font.loadFromFile("font.TTF"))
    {
        cerr<<"font failed to be loaded!";
        return 1; //error occured
    }

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualization");

	vector<int> list(WIDTH);
	initializeList(list, HEIGHT);
	sf::Time time_taken;
	switch (algo)
	{
	case 1:
		window.setTitle("Selection Sort");
		time_taken = selectionSort(list, window, HEIGHT, font);
		drawText(window, "Time taken: " + to_string(time_taken.asSeconds()) + " sec", sf::Vector2f(1, 45),font);
		break;
	case 2:
		window.setTitle("Bubble Sort");
		time_taken = bubbleSort(list, window, HEIGHT, font);
		drawText(window, "Time taken: " + to_string(time_taken.asSeconds()) + " sec", sf::Vector2f(1, 45),font);
		break;
	case 3:
		window.setTitle("Insertion Sort");
		time_taken = insertionSort(list, window, HEIGHT, font);
		drawText(window, "Time taken: " + to_string(time_taken.asSeconds()) + " sec", sf::Vector2f(1, 45),font);
		break;
	default:
		window.clear();
		drawText(window, "Unavailable option!", sf::Vector2f(WIDTH / 4, HEIGHT / 3),font);
		break;
	}
	window.display();
	while(1)
		handleEvent(window);
	return 0;
}
