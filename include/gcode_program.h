#include <vector>

#include <Arduino.h>

namespace gcode {
    class word_address_data {
    public:
        char letter;
        float val;

        word_address_data() {
            letter = '\0';
            val = -1;
        }

        word_address_data(char l, float f) : letter(l) {
            val = f;
        }

        void printContent(){
            Serial.print(letter);
            Serial.print(val);
            Serial.print(F(" "));
        }
    };

    class block {
    protected:
        std::vector<word_address_data> addresses;


    public:

        uint8_t length;

        block():addresses({}){}
        block(const std::vector<word_address_data> p_chunks) :
            addresses(p_chunks) {
        }


        block(const block& other)
        {
            for (size_t i = 0; i < other.addresses.size(); i++) {
                addresses.push_back(other.addresses[i]);
            }

        }


        block& operator=(const block& other) {
            addresses = other.addresses;

            return *this;
        }



        int size() const { return addresses.size(); }

        const word_address_data& get_add(const int i) {
            if (i < size())
                return addresses[i];
            else
                return addresses[0];
        }

        void printContent(){
            for(word_address_data w:addresses){
                w.printContent();
            }
        }


        std::vector<word_address_data>::const_iterator begin() const { return std::begin(addresses); }
        std::vector<word_address_data>::const_iterator end() const { return std::end(addresses); }

        std::vector<word_address_data>::iterator begin() { return std::begin(addresses); }
        std::vector<word_address_data>::iterator end() { return std::end(addresses); }



    };

    class gcode_program {
    protected:
        std::vector<block> blocks;

    public:
        gcode_program(const std::vector<block>& p_blocks) :
            blocks(p_blocks) {}
        gcode_program():blocks({}) {}

        int num_blocks() const { return blocks.size(); }

        block & get_block(const size_t i) {
            if (i < blocks.size()){
                return blocks[i];
            }
            else
                return blocks[0];
        }

        void removeFirstBlock() { //le probleme G-code vient surement de cette fonction

            for(uint8_t i = 0 ;i < num_blocks()-1;i++){
                blocks[i] = blocks[i+1];
            }

            blocks.pop_back();
        }

        void addBlocks(const std::vector<block>& new_blocks) {
            for(block b:new_blocks){
                blocks.push_back(b);
            }
        }

        void printContent(){
            for(block b:blocks){
                b.printContent();
                Serial.println(F(" "));
            }
        }

        
    };
}