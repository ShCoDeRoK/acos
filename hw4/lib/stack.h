#include <cstring>

template <typename T>
class Stack {

  const int INITIAL_CHECKSUM = 16;
  const int START_CANERY = 15;
  const int FINISH_CANERY = 14;

  char checksum_;
  T* buffer_;
  size_t size_;
  size_t capacity_;
  char* first_;
  char* last_;
  bool debug_;
  
  void expand() {
    T* tmp = new T[2 + capacity_ * 2];
    std::memcpy(tmp, buffer_, (size_ + 1) * sizeof(T));
    if (debug_) {  
      //first canery copied by previous memcpy
      std::memcpy(tmp + capacity_ * 2 + 1, buffer_ + 1 + capacity_, sizeof(T));
    }
    capacity_ *= 2;
    delete buffer_;
    buffer_ = tmp;
  }
  
  void cut() {
    T* tmp = new T[2 + capacity_ / 2];
    std::memcpy(tmp, buffer_, (size_ + 1) * sizeof(T));
    if (debug_) {
      //first canery copied by previous memcpy
      std::memcpy(tmp + 1 + capacity_ / 2, buffer_ + 1 + capacity_, sizeof(T));
    }
    capacity_ /= 2;
    delete buffer_;
    buffer_ = tmp;
  }
  
  void check() {
    
    bool ok = !memcmp(buffer_, first_, sizeof(T));
    ok &= !memcmp(buffer_ + 2 + capacity_ - 1, last_, sizeof(T));
    if (!ok) {
      printf("### Error.\n");
      printf("### Stack was changed.");
      exit(1);
    }
    
    char* current_buffer = (char*)(buffer_ + 1);
    char current_checksum = INITIAL_CHECKSUM; //initial random value
    for (size_t i = 0; i < sizeof(T) * size_; ++i) {
      current_checksum ^= current_buffer[i];
    }
    
    if (current_checksum != checksum_) {
      printf("### Error.\n");
      printf("### Stack's data was changed.\n");
      exit(1);
    }
  }
  
  void changeCheckSum(size_t id) {
    char* ptr = (char*)(buffer_ + id);
    for (size_t i = 0; i < sizeof(T); ++i)
      checksum_ ^= ptr[i];
  }
 public:
  Stack(bool debug) : debug_(debug) {
    size_ = 0;
    capacity_ = 8;
    buffer_ = new T[2 + capacity_];
    
    if (debug) {
      checksum_ = INITIAL_CHECKSUM; //random value
      first_ = (char*)calloc(1, sizeof(T));
      last_ = (char*)calloc(1, sizeof(T));

      for (size_t i = 0; i < sizeof(T); ++i) {
        first_[i] = START_CANERY; //random value
        last_[i] = FINISH_CANERY; //random value
      }
      memcpy(buffer_, first_, sizeof(T));
      memcpy(buffer_ + 2 + capacity_ - 1, last_, sizeof(T));
    }
  }

  ~Stack() {
    delete buffer_;
    if (debug_) {
      delete first_;
      delete last_;
    }
  }
  void push(const T& item) {
    if (debug_) {
      check();
    }
    if (size_ + 1 == capacity_) {
      expand();
    }
    buffer_[1 + size_++] = item;
    if (debug_) {
      changeCheckSum(size_);
    }
  }
  T pop() {
    if (debug_) { 
      check();
    }
    if (size_ == 0) {
      printf("### Error.\n");
      printf("### Stack is empty but operation \'pop\' is called.\n");
      return T();
      //exit(1);
    }
    if (debug_) {
      changeCheckSum(size_);
    }
    T item = buffer_[1 + --size_];
    if (4 * size_ < capacity_ && capacity_ > 8) {
      cut();
    }
    return item;
  }

  size_t getSize() const {
    return size_;
  }
};
