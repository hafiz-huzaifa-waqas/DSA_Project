#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
using namespace std;

struct TreeNode
{
    string genre;
    vector<TreeNode *> children;
};

struct Movie
{
    string name;
    string genre;
    string category;
};

struct Node
{
    string MOVIE;
    string GENRE;
    string CATEGORY;
    Node *next;
};

// Prototypes
int getIntegerInput();          // Function to safely get integer input from user
TreeNode *createGenreTree();    // Function to create genre hierarchy tree
TreeNode *createCategoryTree(); // Function to create category hierarchy tree
string toLowerCase(string str); // Function to convert string to lowercase

// functions for file handling and movie management I.E ADMIN MODE functions

Movie AddMovie(vector<Movie> Mov, vector<string> Genre, vector<string> Category); // Function to add a new movie to the list and file
vector<Movie> DeleteMovie(vector<Movie> Mov);                                     // Function to delete a movie from the list and file
vector<Movie> MoviesInFile();                                                     // Function to read movies from file and return as a vector


// functions to search and sort movies I.E USER MODE functions

void sortMoviesAZ(vector<Movie> movies, int size);                                       // Function to sort movies alphabetically
void SearchMovieByGenre(vector<Movie> MoviesList, vector<string> Genre, int size);       // Function to search for movies by genre
void SearchMovieByCategory(vector<Movie> MoviesList, vector<string> Category, int size); // Function to search for movies by category
void searchMovieByName(vector<Movie> MoviesList, int size);                              // Function to search for movies by name
void MoviesWithGivenInitial(vector<Movie> MoviesList, int size);                         // Function to find movies with a given initial

void SelectMovieFromList(vector<Movie> movies, vector<Movie> matchedMovies, int size); // Function to select a movie from a list of matched movies

// functions related to recommendations OR related to Linked List

void AddRecommendationsToLL(Node *&head, Movie movie);                                 // Function to add a movie to the recommendations linked list
vector<Movie> TraversingRecommendations(Node *head);                                   // Function to traverse the recommendations linked list
void RemoveRecommendationsFromLL(Node *head);                                          // Function to remove a movie from the recommendations linked list OR to clear the linked list
int main()
{

    cout << "========================================" << endl;
    cout << "\tMOVIE RECOMMENDATION SYSTEM" << endl;
    cout << "========================================" << endl;

    TreeNode *genreTree = createGenreTree();
    vector<string> Genre;
    for (auto child : genreTree->children)
    {
        Genre.push_back(child->genre);
    }

    TreeNode *categoryTree = createCategoryTree();
    vector<string> Category;
    for (auto child : categoryTree->children)
    {
        Category.push_back(child->genre);
    }

    int mode;

    vector<Movie> MoviesList = MoviesInFile();
    do
    {
        cout << "========================================" << endl;
        cout << "\t\tMODES" << endl;
        cout << "========================================" << endl;

        cout << "1.Admin \n2.User \n-1.Exit" << endl;
        cout << "choose your Mode OR -1 to exit: ";
        mode = getIntegerInput();

        if (mode == 1)
        {
            cout << "Hint: Username = admin & Password = admin123" << endl;
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (username == "admin" && password == "admin123")
            {

                int choice;
                do
                {
                    cout << "\n1. Add Movie" << endl;
                    cout << "2. Delete Movie" << endl;
                    cout << "-1. Back to Mode selection" << endl;

                    cout << "\nEnter one choice: ";
                    choice = getIntegerInput();
                    switch (choice)
                    {

                    case 1:
                    {
                        Movie NewMovie = AddMovie(MoviesList, Genre, Category);
                        MoviesList.push_back(NewMovie);
                        break;
                    }
                    case 2:
                        MoviesList = DeleteMovie(MoviesList);
                        break;

                    case -1:
                        cout << "Back to Mode selection\n";
                        break;

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }

                } while (choice != -1);
            }
            else
            {
                cout << endl
                     << "invalid Username or Password" << endl;
                cout << "Back to Mode selection\n"
                     << endl;
            }
        }
        else if (mode == 2)
        {

            int size = MoviesList.size();

            int choice;

            do
            {
                cout << "=========================" << endl;
                cout << "\tHOME PAGE" << endl;
                cout << "=========================" << endl;
                cout << "\n1. Search Movie by Name" << endl;
                cout << "2. Browse Movies by Genre" << endl;
                cout << "3. Sort A-Z" << endl;
                cout << "4. Movies with Given Initial" << endl;
                cout << "5. Browse Movies by Category" << endl;
                cout << "-1. Back to Mode selection" << endl;
                cout << "\nEnter one choice: ";
                choice = getIntegerInput();

                switch (choice)
                {
                case 1:
                {
                    searchMovieByName(MoviesList, size);
                    break;
                }

                case 2:
                {
                    SearchMovieByGenre(MoviesList, Genre, size);
                    break;
                }

                case 3:
                    sortMoviesAZ(MoviesList, size);
                    break;

                case 4:
                    MoviesWithGivenInitial(MoviesList, size);
                    break;
                case 5:
                    SearchMovieByCategory(MoviesList, Category, size);
                    break;

                case -1:
                    cout << "Back to Mode selection\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                }

            } while (choice != -1);
        }
        else if (mode == -1)
        {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid mode selected. Exiting the program." << endl;
        }
    } while (mode != -1);
    cout << endl;
    cout << "\nThank you for using the Movie Recommendation System!" << endl;
    cout << endl;
    return 0;
}

// Function Definitions
int getIntegerInput()
{
    int choice;
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number.\n";
        return -99;
    }
    return choice;
}

TreeNode *createGenreTree()
{
    TreeNode *root = new TreeNode{"Genres"};

    vector<string> baseGenres = {
        "Action", "Sci-Fi", "Horror", "Comedy", "Romance",
        "Adventure", "Animation", "Crime", "Drama",
        "Fantasy", "Mystery", "Thriller"};

    for (string g : baseGenres)
    {
        TreeNode *node = new TreeNode{g};
        root->children.push_back(node);
    }

    return root;
}

TreeNode *createCategoryTree()
{
    TreeNode *root = new TreeNode{"Categories"};

    vector<string> baseCategories = {
        "Bollywood", "Hollywood", "Tollywood", "Lollywood"};

    for (string g : baseCategories)
    {
        TreeNode *node = new TreeNode{g};
        root->children.push_back(node);
    }

    return root;
}

string toLowerCase(string str)
{
    for (char &c : str)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return str;
}

void AddRecommendationsToLL(Node *&head, Movie movie)
{
    Node *newNode = new Node;
    newNode->MOVIE = movie.name;
    newNode->GENRE = movie.genre;
    newNode->CATEGORY = movie.category;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

vector<Movie> TraversingRecommendations(Node *head)
{
    vector<Movie> recommendedMovies;
    Node *temp = head;

    int count = 0;
    while (temp != nullptr)
    {
        count++;
        recommendedMovies.push_back({temp->MOVIE, temp->GENRE, temp->CATEGORY});
        cout << count << ". " << temp->MOVIE << "    \tGenre: " << temp->GENRE << "\tCategory: " << temp->CATEGORY << endl;
        temp = temp->next;
    }
    return recommendedMovies;
}

void RemoveRecommendationsFromLL(Node *head)
{
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

void SelectMovieFromList(vector<Movie> movies, vector<Movie> matchedMovies, int size)
{
    int subChoice;

    while (true)
    {
        cout << "\nSelect a movie (1-" << matchedMovies.size() << ", -1 to go back): ";
        subChoice = getIntegerInput();

        if (subChoice == -1)
        {
            return;
        }
        if (subChoice < 1 || subChoice > matchedMovies.size())
        {
            cout << "Invalid choice!\n";
            cout << "Try between 1 and " << matchedMovies.size()
                 << " OR enter -1 to go back\n";

            cout << "\nMovies you can select:\n";
            for (int i = 0; i < matchedMovies.size(); i++)
            {
                cout << i + 1 << ". " << matchedMovies[i].name << "\tGenre: " << matchedMovies[i].genre << endl;
            }
            cout << "-1. To go back to previous menu\n";

            continue;
        }
        
        Movie selectedMovie = matchedMovies[subChoice - 1];

        cout << "\nYou selected: " << selectedMovie.name << "\tGenre: " << selectedMovie.genre << "\tCategory: " << selectedMovie.category << endl;

        Node *head = nullptr;

        for (int i = 0; i < size; i++)
        {
            if (movies[i].genre == selectedMovie.genre && movies[i].name != selectedMovie.name)
            {
                AddRecommendationsToLL(head, movies[i]);
            }
        }

        cout << "\nMovies you may also like:\n";
        matchedMovies = TraversingRecommendations(head);

        cout << "-1. To go back to previous menu\n";

        RemoveRecommendationsFromLL(head);
    }
}

vector<Movie> MoviesInFile()
{
    vector<Movie> Mov;

    ifstream inFile("movies.txt");
    if (!inFile)
    {
        cout << "Error opening file!" << endl;
        return vector<Movie>();
    }

    string line;

    while (getline(inFile, line))
    {
        if (line.empty()) continue;         
        stringstream ss(line);
        string movieName, movieGenre, movieCategory;

        getline(ss, movieName, '\t');
        getline(ss, movieGenre, '\t');
        getline(ss, movieCategory);

        Movie temp;
        temp.name = movieName;
        temp.genre = movieGenre;
        temp.category = movieCategory;
        Mov.push_back(temp);
    }

    inFile.close();
    return Mov;
}

Movie AddMovie(vector<Movie> Mov, vector<string> Genre, vector<string> Category)
{
    Movie newMovie;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    cout << "Enter new movie name: " << endl;
    getline(cin, newMovie.name);

    cout << "Enter genre: " << endl;
    getline(cin, newMovie.genre);
    

    for (int i = 0; i < Genre.size(); i++)
    {
        if (newMovie.genre == Genre[i])
        {
            break;
        }
        if (i == Genre.size() - 1)
        {
            cout << "Genre not found! Please enter a valid genre from the list below:\n";
            for (int j = 0; j < Genre.size(); j++)
            {
                cout << j + 1 << ". " << Genre[j] << endl;
            }
            cout << "Enter genre: ";
            getline(cin, newMovie.genre);
            i = -1;
        }
    }

    cout << "Enter category: " << endl;
    getline(cin, newMovie.category);

    for (int i = 0; i < Category.size(); i++)
    {
        if (newMovie.category == Category[i])
        {
            break;
        }
        if (i == Category.size() - 1)
        {
            cout << "Category not found! Please enter a valid category from the list below:\n";
            for (int j = 0; j < Category.size(); j++)
            {
                cout << j + 1 << ". " << Category[j] << endl;
            }
            cout << "Enter category: ";
            getline(cin, newMovie.category);
            i = -1;
        }
    }

    ofstream outFile("movies.txt", ios::app); // Add new data to file without over writing it
    if (outFile.is_open())
    {
        outFile << "\n"
                << newMovie.name << "\t" << newMovie.genre << "\t" << newMovie.category << endl;
        outFile.close();
        cout << "Movie added successfully!\n";
    }
    else
    {
        cout << "Error opening file for writing!" << endl;
    }
    return newMovie;
}

vector<Movie> DeleteMovie(vector<Movie> Mov)
{
    int choice;

    cout << "1. To delete by name\n2. delete by selected movie from list\n-1. To go back to previous menu" << endl;
    cout << "Enter choice: ";
    choice = getIntegerInput();
    bool deleted = false;

    switch (choice)
    {
    case 1:
    {
        string movieName;
        cout << "Enter movie name to delete: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, movieName);
        auto it = remove_if(Mov.begin(), Mov.end(), [&](const Movie &m)
                            { return toLowerCase(m.name) == toLowerCase(movieName); });
        if (it != Mov.end())
        {
            Mov.erase(it, Mov.end());
            deleted = true;
        }
        else
        {
            cout << "Movie not found!\n";
        }
        break;
    }
    case 2:
    {
        for (int i = 0; i < Mov.size(); i++)
        {
            cout << i + 1 << ". " << Mov[i].name << "\tGenre: " << Mov[i].genre << "\tCategory: " << Mov[i].category << endl;
        }

        int subchoice;
        cout << "Enter choice to delete: ";
        subchoice = getIntegerInput();

        if (subchoice < 1 || subchoice > Mov.size())
        {
            cout << "Invalid choice!" << endl;
            return Mov;
        }

        Mov.erase(Mov.begin() + (subchoice - 1));
        deleted = true;
        break;
    }
    case -1:
    {
        cout << "Back to previous menu\n";
        return Mov;
    }
    default:
    {
        cout << "Invalid choice!\n";
        return Mov;
    }
    }
     
    if (deleted)
    {
        ofstream outFile("movies.txt", ios::out); // over writes file with new vector
        if (outFile.is_open())
        {
            for (auto &movie : Mov)
            {
                outFile << movie.name << "\t" << movie.genre << "\t" << movie.category << endl;
            }
            outFile.close();
            cout << "Movie deleted successfully!\n";
        }
        else
        {
            cout << "Error opening file for writing!" << endl;
        }
    }
    return Mov;
}

void sortMoviesAZ(vector<Movie> movies, int size)
{
    vector<Movie> movieList;
    for (int i = 0; i < size; i++)
    {
        movieList.push_back(movies[i]);
    }

    sort(movieList.begin(), movieList.end(), [](const Movie &a, const Movie &b)
         { return a.name < b.name; });

    cout << "\nMovies Sorted from A → Z:\n";
    Node *head = nullptr;
    for (int i = 0; i < movieList.size(); i++)
    {
        AddRecommendationsToLL(head, movieList[i]);
    }
    TraversingRecommendations(head);
    RemoveRecommendationsFromLL(head);
}

void SearchMovieByGenre(vector<Movie> MoviesList, vector<string> Genre, int size)
{

    int genchoice;
    string selectedgenre;
    do
    {
        cout << "\nSelect Genre: \n";
        for (int i = 0; i < Genre.size(); i++)
        {
            cout << i + 1 << ". " << Genre[i] << endl;
        }
        cout << "-1. To go back to home page\n";
        cout << "\nEnter your choice: ";
        genchoice = getIntegerInput();

        if (genchoice < 1 || genchoice > Genre.size())
        {
            cout << "Invalid choice!\n";
            cout << "Try between 1 and " << Genre.size() << " OR enter -1 to go back to home page\n";
        }
        else
        {
            selectedgenre = Genre[genchoice - 1];

            cout << "\nMovies in " << selectedgenre << " Genre:\n";

            int count = 0;
            vector<Movie> matchedMovies;
            for (int i = 0; i < size; i++)
            {
                if (MoviesList[i].genre == selectedgenre)
                {
                    count++;
                    cout << count << ". " << MoviesList[i].name << "    \tGenre: " << MoviesList[i].genre << "\tCategory: " << MoviesList[i].category << endl;
                    matchedMovies.push_back(MoviesList[i]);
                }
            }

            if (count == 0)
            {
                cout << "No movies found in this genre.\n";
            }
            else
            {
                SelectMovieFromList(MoviesList, matchedMovies, size);
            }
        }
        
    } while (genchoice != -1);
}

void SearchMovieByCategory(vector<Movie> MoviesList, vector<string> Category, int size)
{
    int catchoice;
    string selectedcategory;
    cout << "\nSelect Category: \n";
    for (int i = 0; i < Category.size(); i++)
    {
        cout << i + 1 << ". " << Category[i] << endl;
    }
    cout << "-1. To go back to home page\n";
    cout << "\nEnter your choice: ";
    catchoice = getIntegerInput();
    do
    {

        if (catchoice < 1 || catchoice > Category.size())
        {
            cout << "Invalid choice!\n";
            cout << "Try between 1 and " << Category.size() << " OR enter -1 to go back to home page\n";
        }
        else
        {
            selectedcategory = Category[catchoice - 1];

            cout << "\nMovies in " << selectedcategory << " Category:\n";

            int count = 0;
            vector<Movie> matchedMovies;

            for (int i = 0; i < size; i++)
            {
                if (MoviesList[i].category == selectedcategory)
                {
                    count++;
                    cout << count << ". " << MoviesList[i].name << "    \tGenre: " << MoviesList[i].genre << "\tCategory: " << MoviesList[i].category << endl;
                    matchedMovies.push_back(MoviesList[i]);
                }
            }

            if (count == 0)
            {
                cout << "No movies found in this category.\n";
            }
            else
            {
                SelectMovieFromList(MoviesList, matchedMovies, size);
            }
        }
        cout << "\nSelect Category: \n";
        for (int i = 0; i < Category.size(); i++)
        {
            cout << i + 1 << ". " << Category[i] << endl;
        }
        cout << "-1. To go back to home page\n";
        cout << "\nEnter your choice: ";
        catchoice = getIntegerInput();
    } while (catchoice != -1);
}

void searchMovieByName(vector<Movie> MoviesList, int size)
{
    string search_movie;

    cout << "\nEnter Movie Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, search_movie);

    vector<Movie> matchedMovies;

    for (int i = 0; i < size; i++)
    {
        if (toLowerCase(MoviesList[i].name).find(toLowerCase(search_movie)) != string::npos)
        {
            matchedMovies.push_back(MoviesList[i]);
        }
    }

    if (matchedMovies.empty())
    {
        cout << "Movie not found\n";
    }
    else
    {
        cout << "\nMatched Movies:\n";
        for (int i = 0; i < matchedMovies.size(); i++)
        {
            cout << i + 1 << ". " << matchedMovies[i].name << "    \tGenre: " << matchedMovies[i].genre << "\tCategory: " << matchedMovies[i].category << endl;
        }
        cout << "-1. To go back to previous menu\n";

        SelectMovieFromList(MoviesList, matchedMovies, size);
    }
}

void MoviesWithGivenInitial(vector<Movie> MoviesList, int size)
{
    char initial;
    cout << "\nEnter the initial character: ";
    cin >> initial;

    vector<Movie> matchedMovies;

    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (!MoviesList[i].name.empty() && tolower(MoviesList[i].name[0]) == tolower(initial))
        {
            count++;
            cout << count << ". " << MoviesList[i].name << endl;
            matchedMovies.push_back(MoviesList[i]);
        }
    }
    cout << "-1. To go back to previous menu\n";

    if (matchedMovies.empty())
    {
        cout << "No movies found starting with '" << initial << "'.\n";
    }
    else
    {
        SelectMovieFromList(MoviesList, matchedMovies, size);
    }
}