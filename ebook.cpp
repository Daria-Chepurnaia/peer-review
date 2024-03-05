#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const size_t users_num = 100000;

class EBook {
public:
    EBook() {id_to_page_.resize(users_num, 0);}
    
    void Read(int id, int page) {        
        size_t size = page_to_readers_num_.size();
        int user_pages_num = id_to_page_[id - 1];        

        if (user_pages_num == 0) {
            user_num_++;                 
        }
        if (page > size) {
           AddUsersRead (user_pages_num, size);
           AddNewPages(page);  
        } else {
           AddUsersRead (user_pages_num, page);
        }
        id_to_page_[id - 1] = page;    
    }
    
    double Cheer(int id) {        
        if (user_num_ == 0 || page_to_readers_num_[id_to_page_[id - 1]-1] == 0){
            return 0;
        }
        if (page_to_readers_num_[id_to_page_[id - 1]-1] == 1) {
            return 1;
        } 
        return (user_num_ - page_to_readers_num_[id_to_page_[id - 1]-1]) / double(user_num_-1);         
    }    
   
private:
    vector<int> id_to_page_;
    vector<int> page_to_readers_num_;
    int user_num_{};
    
    void AddUsersRead (int begin, int end) {
        for (int i = begin; i < end; ++i) {
            page_to_readers_num_[i]++;     
        }
    }
    void AddNewPages(int max_page) {
        for (int i = page_to_readers_num_.size(); i < max_page; ++i) {
            page_to_readers_num_.push_back(1);
        }
    }
};

int main() {
    int cmnds_num;
    cin >> cmnds_num;
    EBook book;
    cout << setprecision(6);
    for (int i = 0; i < cmnds_num; ++i) {        
        string cmnd;
        int id;
        cin >> cmnd >> id;    
        if (cmnd[0] == 'C') {
           cout << book.Cheer(id) << endl;
        } else {
            int page;
            cin >> page;
            book.Read(id, page);
        }        
    }
}