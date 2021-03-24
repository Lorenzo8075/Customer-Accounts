#include <iostream>
#include <exception>
#include <map>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class AccountNotFoundException: public exception{
    private:
        string phone_number;
    public:
        virtual const char* what() const noexcept override;
};
const char* AccountNotFoundException:: what() const noexcept{
     
    return " Account does not exist!";  
}

class Media{
    private:
        double size; // in MB
    public:
        static const double DEFAULT_SIZE;
        static const double DEFAULT_CHARGE_PER_MB;
        static const double DEFAULT_MINIMUM_CHARGE;
        static const double DEFAULT_SIZE_THRESHOLD;

        Media();
        Media(double size);
        ~Media();
        double get_size()const;
        void set_size(double size);
        double GetCharge(double size);
};

const double Media::DEFAULT_SIZE = 0.0;
const double Media::DEFAULT_CHARGE_PER_MB = 0.05;
const double Media::DEFAULT_MINIMUM_CHARGE = 1.00;
const double Media::DEFAULT_SIZE_THRESHOLD = 100.00;

template <class T>
class Message{
    private:
        string to;
        T m_data;

    public:
        static const string DEFAULT_DATA;
        Message();
        Message(string to, T data);
        ~Message();
        T get_data() const;
        void set_data(T data);
        string get_to()const;
        void set_to(string to);
};
template <class T> const string Message<T>::DEFAULT_DATA = "000-000-0000";

class SmartCarrier{
    private:
        string carrier_name;
        bool init;
        map<string, vector<Message<Media>*> > account_list;//no need to declare constructor. It should be properly "initialized" to an empty map object when a SmartCarrier object is instantiated.
        void Menu();
        int GetChoice();
        void ListAccounts();
        void InsertMessage();
        void PurgeLargeMessages();
        void DisconnectAccount();
        void Quit();

    public:
        static const string DEFAULT_CARRIER_NAME;
        static const bool DEFAULT_INIT; 
        SmartCarrier();
        SmartCarrier(string carrier_name, bool init); 
        ~SmartCarrier();
        void Init();
        void StartService();
};

const string SmartCarrier::DEFAULT_CARRIER_NAME = "XYZ Wireless";
const bool SmartCarrier::DEFAULT_INIT = false;

int main(){
    SmartCarrier* p_smart_carrier = new SmartCarrier();
    
    p_smart_carrier->Init();
    p_smart_carrier->StartService();
    delete p_smart_carrier;
    return 0;
}

Media::Media(): size(Media::DEFAULT_SIZE){}
Media::Media(double size):size(size){}
Media::~Media(){}
double Media::get_size()const{return size;}
void Media::set_size(double size){this->size = size;}
double Media::GetCharge(double size){
    if(size == DEFAULT_SIZE){
        return DEFAULT_SIZE;
    }
    if(DEFAULT_CHARGE_PER_MB * size > DEFAULT_MINIMUM_CHARGE){
        return DEFAULT_CHARGE_PER_MB * size;
    }
    else{
        return DEFAULT_MINIMUM_CHARGE;
    }
}

template<class T>
Message<T>::Message(){}
template<class T>
Message<T>::Message(string to, T data): to(to), m_data(data){}
template<class T>
Message<T>::~Message(){}
template<class T>
T Message<T>::get_data()const{return m_data;}
template<class T>
void Message<T>::set_data(T data) {m_data = data;}
template<class T>
string Message<T>::get_to()const{return to;}
template<class T>
void Message<T>::set_to(string to){this->to = to;}

SmartCarrier::SmartCarrier():carrier_name(SmartCarrier::DEFAULT_CARRIER_NAME), init(SmartCarrier::DEFAULT_INIT){}
SmartCarrier::SmartCarrier(string carrier_name, bool init):carrier_name(carrier_name), init(init){}

SmartCarrier::~SmartCarrier(){
    map<string, vector<Message<Media>*> >::iterator phone_number_iter;//phone number iter
    vector<Message<Media>*>::iterator message_iter;//message iter

    for(phone_number_iter = account_list.begin(); phone_number_iter != account_list.end(); phone_number_iter++){
        for(message_iter = phone_number_iter->second.begin();message_iter!=phone_number_iter->second.end();message_iter++){
            delete(*message_iter); //free memory/delete all the message pointers
        }
        phone_number_iter->second.clear();//clearing the vector to be extra sure
    }
    account_list.clear();//clering the values in the map
}

void SmartCarrier::Init(){
    account_list["669-444-4444"].push_back(new Message<Media>(Message<Media>::DEFAULT_DATA, Media(Media::DEFAULT_SIZE)));

    account_list["831-777-7777"].push_back (new Message<Media>("408-222-2222", Media(12.89)));//add an account with only one message
    account_list["831-777-7777"].push_back (new Message<Media>("408-435-111", Media(11.08)));
    account_list["831-777-7777"].push_back (new Message<Media>("408-132-111", Media(110.01)));

    //adding accounts with mupltiple messages
    account_list["408-111-1111"].push_back(new Message<Media>("415-678-9011", Media(100.08))); 
    account_list["408-111-1111"].push_back(new Message<Media>("308-555-8888", Media(75.35))); 
    account_list["408-111-1111"].push_back(new Message<Media>("408-908-8888", Media(211.88)));
    account_list["408-111-1111"].push_back(new Message<Media>("321-908-8888", Media(11.33))); 
    account_list["408-111-1111"].push_back(new Message<Media>("000-908-8888", Media(421.99)));  
    account_list["999-333-5555"].push_back(new Message<Media>("213-342-7777", Media(127.39))); 
    account_list["360-222-1414"].push_back(new Message<Media>("626-444-2222", Media(90.14))); 
    account_list["111-222-3333"].push_back(new Message<Media>("806-234-0000", Media(289.29))); 
    account_list["111-222-3333"].push_back(new Message<Media>("896-234-0000", Media(10.56))); 
    account_list["111-222-3333"].push_back(new Message<Media>("866-234-0000", Media(1.12))); 
    account_list["333-222-3333"].push_back(new Message<Media>("816-234-0000", Media(35.54))); 
    account_list["333-222-3333"].push_back(new Message<Media>("826-234-0000", Media(123.73))); 
    account_list["333-222-3333"].push_back(new Message<Media>("876-634-0000", Media(74.09))); 
    account_list["333-222-3333"].push_back(new Message<Media>("876-134-0000", Media(56.67))); 
    account_list["142-387-2034"].push_back(new Message<Media>("876-834-0000", Media(21.49))); 
    account_list["908-262-1231"].push_back(new Message<Media>("876-934-0000", Media(111.29))); 
    account_list["626-342-4944"].push_back(new Message<Media>("876-034-0000", Media(10.16))); 
    account_list["360-222-3333"].push_back(new Message<Media>("876-634-0000", Media(121.19))); 
    account_list["360-222-3333"].push_back(new Message<Media>("876-534-0000", Media(12.11))); 
    init = true;
}

void SmartCarrier::Menu(){
    cout << setw(27) << "VODAFONE" << endl << endl;
    cout << '\t' << '\t' << "ACCOUNT ADMIN" << endl << endl;
    cout << "1. List all accounts and their messages' usages" << endl;
    cout << "2. Add a message to an account" << endl;
    cout << "3. Purge large messages from an account" << endl;
    cout << "4. Disconnect an account" << endl;
    cout << "5. Quit" << endl;
}

int SmartCarrier::GetChoice(){
    int user_option;
    cout << "Select an option (1-5): ";
    cin >> user_option;
    if(user_option <= 0 || user_option >5){
        throw 0;
    }
    return user_option; 
} 

void SmartCarrier::StartService(){
    int selected_user_option;
    if(!init){
        cout << "System not initialized. Exiting..." << endl;
    }
    else{
        do{
            try{
                Menu();
                selected_user_option = GetChoice();
                switch(selected_user_option){
                    case 1:
                    ListAccounts();
                    break;
                    case 2:
                    InsertMessage();
                    break;
                    case 3:
                    PurgeLargeMessages();
                    break;
                    case 4:
                    DisconnectAccount();
                    break;
                    case 5:
                    Quit();
                    break;
                }
            }

            catch(AccountNotFoundException &account_not_found){
                AccountNotFoundException account_not_found_exception;
                cout << account_not_found_exception.what() << endl;
            }
            catch(...){
                cout << "Invalid selection. Please select a number between 1-5."<< endl;//error message try again
            }
        }
        while(selected_user_option != 5);
              
    }
}

void SmartCarrier::ListAccounts(){
    cout << "Account" << setw(20) << "Total Messages" << setw(31) << "Total Messages' sizes (MB)" << setw(19) << "Charge(dollar)" << endl << endl;
    map<string, vector<Message< Media>*> >::iterator phone_number_iter;
    vector<Message<Media>*>::iterator message_iter;
    
    int message_count = 0;
    double total_message_size = 0;
    double total_charge = 0;
    
    for(phone_number_iter = account_list.begin(); phone_number_iter!= account_list.end(); phone_number_iter++){
        cout << phone_number_iter->first << setw(9);
        for(message_iter = phone_number_iter->second.begin(); message_iter!= phone_number_iter->second.end(); ++message_iter){
            total_message_size += (*message_iter)->get_data().get_size();                        
            message_count++;
        }
            total_charge = (*phone_number_iter->second.begin())->get_data().GetCharge(total_message_size);
            cout << message_count << setw(25) << total_message_size << setw(20) << "$" << fixed << setprecision (2)<< total_charge << endl;
            message_count = 0;
            total_message_size = 0;
            total_charge = 0;    
    }

    cout << endl;
}

void SmartCarrier::InsertMessage(){
    string phone_number;
    double media_size;
    cout << "Enter a phone number: " << endl;
    cin >> phone_number;

    map<string, vector<Message<Media>*> >::iterator phone_number_iter;
    phone_number_iter = account_list.find(phone_number);

    if(phone_number_iter == account_list.end()){
        AccountNotFoundException account_not_found;
        throw account_not_found;
    }
    if(phone_number_iter != account_list.end()){
        cout << "Enter Media size: " << endl;
        cin >> media_size;
        account_list[phone_number].push_back(new Message <Media>(phone_number, Media(media_size)));            
    }
}

void SmartCarrier::PurgeLargeMessages(){
    string phone_number;
    double total_deleted_message_size = 0.0;
    cout << "Enter a phone number: " << endl;
    cin >> phone_number;
    map<string, vector<Message<Media>*> >::iterator phone_number_iter;
    vector<Message<Media>*>::iterator message_iter;

    phone_number_iter = account_list.find(phone_number);

    if(phone_number_iter == account_list.end()){
        AccountNotFoundException account_not_found;
        throw account_not_found;
        
    }
    for(message_iter = phone_number_iter->second.begin(); message_iter!= phone_number_iter->second.end(); ++message_iter){ 
        if((*message_iter)->get_data().get_size() > (*message_iter)->get_data().DEFAULT_SIZE_THRESHOLD){
            total_deleted_message_size += (*message_iter)->get_data().get_size();
            delete (*message_iter);//free memory
            phone_number_iter->second.erase(message_iter);//erasing element
            message_iter--;
        }
    }
    cout << endl;
    cout << "Total MB deleted: " << total_deleted_message_size << endl;
    }

void SmartCarrier::DisconnectAccount(){
    string phone_number;
    cout << "Enter a phone number: " << endl;
    cin >> phone_number;
    map<string, vector<Message<Media>*> >::iterator phone_number_iter;
    vector<Message<Media>*>::iterator message_iter;
    phone_number_iter = account_list.find(phone_number);

    if(phone_number_iter == account_list.end()){
        AccountNotFoundException account_not_found;
        throw account_not_found;
    }
    
    for(message_iter = phone_number_iter->second.begin(); message_iter!= phone_number_iter->second.end(); ++message_iter){
        if(phone_number_iter != account_list.end()){
            delete (*message_iter);//free all Message pointers
        } 
    }
   phone_number_iter->second.clear();//clear the vector
   account_list.erase(phone_number_iter);
    
}

void SmartCarrier::Quit(){
    cout << "Program terminated..." << endl;
}
