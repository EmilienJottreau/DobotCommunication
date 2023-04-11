#include <vector>
#include <HardwareSerial.h>


namespace gcode {
    class world_address_data {
    public:
        char letter;
        float val;

        world_address_data() {
            letter = '\0';
            val = -1;
        }

        world_address_data(char l, float f) : letter(l) {
            val = f;
        }
    };

    class block {
    protected:
        std::vector<world_address_data> addresses;


    public:

        uint8_t length;

        block():addresses({}){}
        block(const std::vector<world_address_data> p_chunks) :
            addresses(p_chunks) {
        }


        block(const block& other)
        {
            for (size_t i = 0; i < other.addresses.size(); i++) {
                addresses.push_back(other.addresses[i]);
            }

        }

        block& operator=(const block& other) {
            for (size_t i = 0; i < other.addresses.size(); i++) {
                addresses.push_back(other.addresses[i]);
            }

            return *this;
        }



        int size() const { return addresses.size(); }

        const world_address_data& get_add(const int i) {
            if (i < size())
                return addresses[i];
            else
                return addresses[0];
        }



        std::vector<world_address_data>::const_iterator begin() const { return std::begin(addresses); }
        std::vector<world_address_data>::const_iterator end() const { return std::end(addresses); }

        std::vector<world_address_data>::iterator begin() { return std::begin(addresses); }
        std::vector<world_address_data>::iterator end() { return std::end(addresses); }



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

        void removeFirstBlock() {
            //blocks.erase(blocks.begin());
            //blocks.pop_front();
            std::move(blocks.back());
            blocks.pop_back();
            
        }

        void addBlocks(const std::vector<block>& new_blocks) {
            /*Serial.print("nb blocks : ");
            Serial.println(num_blocks());
            for(block b:blocks){
                Serial.print("taille blocks dans add_blocks : ");
                Serial.println(b.size());
            } 
            for(block b:new_blocks){
                Serial.print("taille new_blocks dans add_blocks : ");
                Serial.println(b.size());
            }   
            std::vector<block> temp_blocks = blocks;
            temp_blocks.insert(temp_blocks.end(), new_blocks.begin(), new_blocks.end());
            blocks = temp_blocks;*/
            for(block b:new_blocks){
                blocks.push_back(b);
            }
            /*for(block b:blocks){
                Serial.print("taille blocks apres add_blocks : ");
                Serial.println(b.size());
            } */
        }

        
    };
}