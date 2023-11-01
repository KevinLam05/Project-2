#include<iostream>
#include<memory>
#include<vector>
#include<string>
// Write template class Tab here
class Tab {
    public:
        Tab(const std::string& url, const std::string& name, const double memory) : url_(url), name_(name), memory_(memory) {}
        const std::string& name() const { return name_;}
        const std::string& url() const { return url_;}
        double memory() const { return memory_;}
        Tab* next = nullptr;
        Tab* prev = nullptr;
    private:
    std::string url_;
    std::string name_;
    double memory_;
};
// Write template class Browser here
template <typename T>
class Browser {
    public:
        Browser() : head_(nullptr), tail_(nullptr), current_tab_(nullptr) {}
        
        void addNewTab(const std::string& url, const std::string& name, const int memory) {
            Tab* tab1 = new Tab(url, name, memory);
            if (head_ == nullptr) {
                head_ = tab1;
                tail_ = tab1;
            } else {
                tail_->next = tab1;
                tab1->prev = tail_;
                tail_ = tab1;
            }
            current_tab_ = tab1;
        }
        void switchToPrevTab() {
            if (current_tab_->prev != nullptr) {
                current_tab_ = current_tab_->prev;
                std::cout << current_tab_->url() << std::endl;
                std::cout << current_tab_->name() << std::endl;
                std::cout <<  current_tab_->memory() << std::endl;
            } else {
                std::cout << "No previous tab \n";
            }
        }
        void switchToNextTab() {
            if (current_tab_->next != nullptr) {
                current_tab_ = current_tab_->next;
                std::cout << current_tab_->url() << std::endl;
                std::cout << current_tab_->name() << std::endl;
                std::cout <<  current_tab_->memory() << std::endl;
            } else {
                std::cout << "No next tab \n";
            }
        }
        void closeCurrentTab() {
            if (current_tab_->next != nullptr) {
                current_tab_ = current_tab_->next;
                std::cout << "Now the current tab is = " << current_tab_->name() << std::endl;
            } else {
                current_tab_ = nullptr;
                delete current_tab_;
            }
        }
        void bookmarkCurrent() {
            if (current_tab_ != nullptr) {
                std::pair<std::string, std::string> bookmark(current_tab_->name(), current_tab_->url());
                bookmarks_.push_back(bookmark);
            }
        }
        void showBookmarkTab() {
            std::cout << "Bookmarks: " << std::endl;
            for (auto& bookmark : bookmarks_) {
                std::cout << bookmark.first << "(" << bookmark.second << ")" << std::endl;
            }
        }
        void moveCurrentToFirst() {
            if (current_tab_ != nullptr) {
                if (current_tab_->prev != nullptr) {
                    current_tab_->prev->next = current_tab_->next;
                }
                if (current_tab_->next != nullptr) {
                    current_tab_->next->prev = current_tab_->prev;
                }
                current_tab_->next = head_;
                head_->prev = current_tab_;
                head_ = current_tab_;
                current_tab_->prev = nullptr;
            }
        }
        int total_memory() {
            int total_memory_;
            for (Tab* tab = head_; tab != nullptr; tab = tab->next) {
                total_memory_ += tab->memory();
            }
            return total_memory_;
        }
        void deleteTab() {
            Tab* high_mem_tab_ = head_;
            Tab* current_tab_ = head_->next;
            while (current_tab_ != nullptr) {
                if (current_tab_->memory() > high_mem_tab_->memory()) {
                    high_mem_tab_ = current_tab_;
                }
                current_tab_ = current_tab_->next;
            }
            if (high_mem_tab_ == head_) {
                head_ = head_->next;
            } else if (high_mem_tab_ == tail_) {
                tail_ = tail_->prev;
            } else {
                high_mem_tab_->prev->next = high_mem_tab_->next;
                high_mem_tab_->next->prev = high_mem_tab_->prev;
            }
            delete high_mem_tab_;
        }
        void display(){
            auto curr = head_;
            std::cout<<"Browser tab list = "<<std::endl;
        while(curr){
            std::cout<<"| "<<curr->name()<<" x|-->";
            curr = curr->next;
        }
    std::cout<<std::endl;
    std::cout<<std::endl;
}
    private:
        Tab* head_;
        Tab* tail_;
        Tab* current_tab_;
        std::vector<std::pair<std::string, std::string>> bookmarks_;
};
//Add display method in Browser template class


int main(){
Browser<double> b1;
b1.addNewTab("https://www.google.com","Google",23.45);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to Next tab = "<<std::endl;
b1.switchToNextTab();
b1.addNewTab("https://www.youtube.com","YouTube",56);
b1.bookmarkCurrent();
b1.display();
b1.addNewTab("https://www.geeksforgeeks.com","GeeksForGeeks",45.78);
b1.bookmarkCurrent();
b1.addNewTab("https://chat.openai.com","ChatGPT",129);
b1.addNewTab("https://linkedin.com","LinkedIn",410);
b1.bookmarkCurrent();
b1.addNewTab("https://github.com","Github",110);
b1.addNewTab("https://kaggle.com","Kaggle",310);
b1.bookmarkCurrent();
b1.display();
std::cout<<"Total memory consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.showBookmarkTab();
b1.moveCurrentToFirst();
b1.display();
b1.deleteTab();
b1.display();
std::cout<<"Switch to next tab = "<<std::endl;
b1.switchToNextTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
b1.showBookmarkTab();
std::cout<<"Total Memory Consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.deleteTab();
b1.display();
b1.addNewTab("https://docs.google.com/","Google Docs",102.34);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.bookmarkCurrent();
b1.showBookmarkTab();
b1.total_memory();
b1.deleteTab();
b1.display();
return 0;
}