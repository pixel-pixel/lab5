#include <iostream>

using namespace std;
//максимальна довжина слова
const int SIZE_OF_WORD = 20;

void print_char_arr(char* arr){
    int index = 0;

    while(index < SIZE_OF_WORD && arr[index] != '\0') {
        cout << arr[index];
        index++;
    }

}

void copy_char_arr(char* from, char* to){
    for(int i = 0; i < SIZE_OF_WORD; i++){
        to[i] = from[i];
    }
}

struct node {
    char eng[SIZE_OF_WORD];
    char ukr[SIZE_OF_WORD];
    int count = 0;

    node(char* e, char* u) {
        copy_char_arr(e, eng);
        copy_char_arr(u, ukr);
    }

    node(char* e, char* u, int n){
        copy_char_arr(e, eng);
        copy_char_arr(u, ukr);
        count = n;
    }

    node *left = nullptr;
    node *right = nullptr;

    int equals(node *nd) {
        if(nd == nullptr) return 0;

            for (int i = 0; i < SIZE_OF_WORD; i++) {
                if(nd->eng[i] == '\0' && eng[i] == '\0') return 0;
                if (eng[i] > nd->eng[i] || nd->eng[i] == '\0') return -1;
                if (eng[i] < nd->eng[i] || eng[i] == '\0') return 1;
            }
            return 0;
    }

    int equals_by_count(node *nd){
        if(nd == nullptr) return 0;

        if(nd->count < count) return -1;
        else if(nd->count > count) return 1;
        else{
            for (int i = 0; i < SIZE_OF_WORD; i++) {
                if(nd->eng[i] == '\0' && eng[i] == '\0') return 0;
                if (eng[i] > nd->eng[i] || nd->eng[i] == '\0') return -1;
                if (eng[i] < nd->eng[i] || eng[i] == '\0') return 1;
            }
            return 0;
        }
    }

    int equals(char *e) {
        for (int i = 0; i < SIZE_OF_WORD; i++) {
            if(e[i] == '\0' && eng[i] == '\0') return 0;
            if (eng[i] > e[i] || e[i] == '\0') return -1;
            if (eng[i] < e[i] || eng[i] == '\0') return 1;
        }
        return 0;
    };
};

//індекс потрібний для спрощення дерева
static int index = 0;
struct tree{
    node* head = nullptr;
    node* local_head = nullptr;
    int size = 0;

    void add(node* nd){
        add(nd, false);
    }

    void get(char* e){
        local_head = head;

        while(true){
            if(local_head->equals(e) == 0) {
                local_head->count++;

                print_char_arr(local_head->ukr);
                cout << endl;
                break;
            }else if(local_head->equals(e) == -1){
                if(local_head->left == nullptr) {
                    cout << "not exist" << endl;
                    break;
                }else local_head = local_head->left;
            }else{
                if(local_head->right == nullptr){
                    cout << "not exist" << endl;
                    break;
                }else local_head = local_head->right;
            }
        }
    }

    node** get_array(){
        index = 0;
        node** arr = new node* [size];
        put_on_index(head, arr);
        return arr;
    }

    void simplification(){
        node** arr = get_array();
        sort(arr, size);
        head = nullptr;
        int pr_size = size;

        for(int i = 0; i < pr_size; i++) add(arr[i], true);
        size = pr_size;
    }

    void print(){
        if(head != nullptr) print(head, 0);
        else cout << "tree is NULL" << endl;
    }

private:
    void add(node* nd, bool sort_by_count){
        size++;

        nd->left = nullptr;
        nd->right = nullptr;

        if(head == nullptr){
            head = nd;
        }else{
            local_head = head;

            if(sort_by_count){
                while (true) {
                    if (local_head->equals_by_count(nd) == -1) {
                        if (local_head->left == nullptr) {
                            local_head->left = nd;
                            break;
                        } else local_head = local_head->left;
                    }else{
                        if(local_head->right == nullptr){
                            local_head->right = nd;
                            break;
                        } else local_head = local_head->right;
                    }
                }
            }else{
                while (true) {
                    if (local_head->equals(nd) == -1) {
                        if (local_head->left == nullptr) {
                            local_head->left = nd;
                            break;
                        } else local_head = local_head->left;
                    }else{
                        if(local_head->right == nullptr){
                            local_head->right = nd;
                            break;
                        } else local_head = local_head->right;
                    }
                }
            }
        }
    }

    void print(node* nd, int tabs){
        cout << '{' << endl;

        for(int i = 0; i <= tabs; i++) cout << '\t';
        cout << "eng = ";
        print_char_arr(nd->eng);
        cout << endl;

        for(int i = 0; i <= tabs; i++) cout << '\t';
        cout << "ukr = ";
        print_char_arr(nd->ukr);
        cout << endl;

        for(int i = 0; i <= tabs; i++) cout << '\t';
        cout << "count = " << nd->count << endl;

        if(nd->left != nullptr){
            cout << endl;
            for(int i = 0; i <= tabs; i++) cout << '\t';
            cout << "left = ";
            print(nd->left, tabs+1);
        }
        if(nd->right != nullptr){
            cout << endl;
            for(int i = 0; i <= tabs; i++) cout << '\t';
            cout << "right = ";
            print(nd->right, tabs+1);
        }

        for(int i = 0; i < tabs; i++) cout << '\t';
        cout << '}' << endl;
    }

    void put_on_index(node* nd, node** arr){
        arr[index] = nd;
        index++;

        if(nd->left != nullptr) put_on_index(nd->left, arr);
        if(nd->right != nullptr) put_on_index(nd->right, arr);
    }

    void sort(node** arr, int size){
        for(int k = 1; k < size; k++){
            for(int i = 0; i < size - k; i++){
                if(arr[i]->count < arr[i+1]->count) swap(arr[i], arr[i+1]);
            }
        }
    }
};

void console(){
    tree t;

    char eng[SIZE_OF_WORD];
    char ukr[SIZE_OF_WORD];
    int c;

    const char* msg_for_help = "----------------------------------------\n"
                               "n - добавити нове слово\n"
                               "g - отримати переклад англійського слова\n"
                               "p - напечатати дерево\n"
                               "s - спростити дерево\n"
                               "x - вийти\n"
                               "----------------------------------------";
    const char* msg_for_eng = "Введіть слово на англійській: ";
    const char* msg_for_ukr = "Введіть слово на українській: ";
    const char* msg_for_count = "Введіть к-ть звернень до слова: ";
    const char* msg_for_translate = "Ваше слово на українській: ";
    const char* msg_for_print = "Ваше дерево: ";
    const char* msg_for_sort = "Дерево спрощено!";

    char ch;

    while (true){
        cout << msg_for_help << endl;
        cin >> ch;

        if(ch == 'n'){
            cout << msg_for_eng << endl;
            cin.get();
            cin.getline(eng, SIZE_OF_WORD);

            cout << msg_for_ukr << endl;
            cin.getline(ukr, SIZE_OF_WORD);;

            cout << msg_for_count << endl;
            cin >> c;

            t.add(new node(eng, ukr, c));
        }else if(ch == 'g'){
            cout << msg_for_eng << endl;
            cin.get();
            cin.getline(eng, SIZE_OF_WORD);
            cout << msg_for_translate << endl;
            t.get(eng);
        }else if(ch == 'p'){
            cout << msg_for_print << endl;
            t.print();
        }else if(ch == 's'){
            t.simplification();
            cout << msg_for_sort << endl;
        }else return;
    }
}

int main() {
    console();

    return 0;
}