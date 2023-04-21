#include "parser.h"

#define ARDUINO_PROGMEM 1
#define DEBUG_PRINT 0


//#include <ctype.h>
#include <avr/pgmspace.h>
#include <HardwareSerial.h>

using namespace std;

namespace gcode {

    bool chars_left(uint16_t currentchar, uint16_t strSize) {
        return currentchar < strSize;
    }

    int parse_int(const char* s, uint8_t* currenttoken) {

        int i = atoi(s);
        *currenttoken += 1;
        return i;
    }

    std::pair<bool, int> parse_line_number(char* s, uint8_t* currenttoken) {
        if (s[0] == 'N') {
            *currenttoken += 1;

            int ln = parse_int(&s[*currenttoken], currenttoken);

            return std::make_pair(true, ln);
        }
        return std::make_pair(false, -1);
    }

    bool parse_slash(char* s, uint8_t* currenttoken) {
        if (s[0] == '/') {
            *currenttoken += 1;
            return true;
        }

        return false;
    }



    bool is_num_char(const char c) {
        return (isdigit(c) ||
            (c == '.') || //pour les floats
            (c == '-'));  //signe negatif
    }

    block parse_tokens(std::vector<string>& tokens) {


        if (tokens.size() == 0) { return block(); }

        uint8_t nb_token = tokens.size();
        uint8_t current_token = 0;
        uint8_t length = 0;
        #if DEBUG_PRINT
        Serial.print("taille du vecteur token : ");
        Serial.println(nb_token);
        #endif
        vector<word_address_data> addresses;
        parse_slash(&tokens[current_token][0], &current_token); //check if line is slashed, ca nous sert a rien je pense


        parse_line_number(&tokens[current_token][0], &current_token); //pas sur que ca serve mais ca peut eviter des bugs

        while (current_token < nb_token) {
            if (isalpha(tokens[current_token][0])) {
                char c = tokens[current_token][0];
                current_token++;
                float f = atof(&tokens[current_token][0]);
                current_token++;
                #if DEBUG_PRINT
                    Serial.print(c);
                    Serial.println(f);
                #endif
                addresses.push_back(word_address_data(c, f));
                length++;

            }
            else {
                current_token++;
            }

        }

        block b = block(addresses);
        b.length = length;
        #if DEBUG_PRINT
            Serial.print("Taille du block apres parse_token : ");
            Serial.println(length);
            Serial.print("Taille de addresses apres parse_token : ");
            Serial.println(addresses.size());
            Serial.print("Taille de block avec b.size(): ");
            Serial.println(b.size());
        #endif
        
        return b;


    }

    string parse_comment_with_delimiters(char sc, char ec, char* s, uint16_t* currentchar, uint16_t strSize) {
        int depth = 0; //nested comment
        string text = "";
        do {
            if (s[*currentchar] == sc) {
                depth++;
                text += s[*currentchar];
            }
            else if (s[*currentchar] == ec) {
                depth--;
                text += s[*currentchar];
            }
            else {
                text += s[*currentchar];
            }
            *currentchar += 1;
        } while (chars_left(*currentchar, strSize) && depth > 0);

        return text;
    }



    std::string digit_string(char* s, uint16_t* currentchar, uint16_t strSize) {
        string num_str = "";

        while (chars_left(*currentchar, strSize) && is_num_char(s[*currentchar])) {
            num_str += s[*currentchar];
            *currentchar += 1;
        }

        return num_str;
    }




    std::string lex_token(char* s, uint16_t* currentchar, uint16_t strSize) {

        char c = s[*currentchar];
        string next_token = "";

        if (is_num_char(c)) {
            return digit_string(&s[0], currentchar, strSize);
        }
        //a ignorer peut etre
        switch (c) {

        case '(':
            return parse_comment_with_delimiters('(', ')', &s[0], currentchar, strSize);

        case '[':
            return parse_comment_with_delimiters('[', ']', &s[0], currentchar, strSize);

        case ')':


        case ']':


        default:
            next_token = c;
            *currentchar += 1;
            return next_token; // pour retourner un string
        }

    }


    void ignore_whitespace(char* s, uint16_t* currentchar, uint16_t strSize) {
        while (chars_left(*currentchar, strSize) && (isspace(s[*currentchar]) || s[*currentchar] == '\r')) { *currentchar += 1; }

    }


    std::vector<std::string> lex_block(std::string& block_text) { //lex peut vouloir dire lexical
        //block_text <=> one line
        uint16_t line_size = block_text.length();
        uint16_t currentchar = 0;

        vector<string> tokens;

        ignore_whitespace(&block_text[0], &currentchar, line_size);

        while (chars_left(currentchar, line_size)) {
            ignore_whitespace(&block_text[0], &currentchar, line_size);

            if (chars_left(currentchar, line_size)) {
                 string token = lex_token(&block_text[0], &currentchar, line_size);
                tokens.push_back(token);
            }
        }

        return tokens;
    }
    std::vector<std::string> lex_block_char(const char* line, uint8_t size) {
        std::string lineString(line, size);
        #if DEBUG_PRINT
            Serial.print("taille de la chaine line dans lex_block_char ");
            Serial.println(lineString.size());
        #endif
        return lex_block(lineString);
    }


    uint16_t progmemStr_GetSize(const char* str) {

#if ARDUINO_PROGMEM
        //reelle ligne dans arduino
        return strlen_P(str);
#else
        //hardcoded pour le moment+
        return strlen(str);
#endif
    }
                //pgm_read_byte_far(pgm_get_far_address(str)+initValue)
    uint8_t progmemStr_findLineSize(const char* str, uint16_t currentCharIndex) {
        uint16_t initValue = currentCharIndex;
#if ARDUINO_PROGMEM
        while (initValue < progmemStr_GetSize(str) && pgm_read_byte_near(str + initValue) != '\n')
#else
        while (initValue < progmemStr_GetSize(str) && str[initValue] != '\n')
#endif
        {
            initValue++;
        }
        return initValue - currentCharIndex;
    }

    void progmemStr_CopyLine(char* dst, uint8_t lineSize, const char* src, uint16_t currentCharIndex) {
        for (int i = 0; i < lineSize; i++) {
#if ARDUINO_PROGMEM
            dst[i] = pgm_read_byte_near(src + currentCharIndex + i);
#endif // ARDUINO_PROGMEM
        }
    }

    vector<block> lex_gprog_char(const char* str) {
        vector<block> blocks;
        uint16_t currentCharIndex = 0;

        while (currentCharIndex < progmemStr_GetSize(str)) {
            uint8_t lineSize = progmemStr_findLineSize(str, currentCharIndex);
            char* line;
            line = (char*)realloc(NULL, lineSize);
            if (line == nullptr) {
                return vector<block>();
            }

            //remplir la ligne
#if ARDUINO_PROGMEM
            //remplir la ligne avec progmem
            progmemStr_CopyLine(line, lineSize, str, currentCharIndex);
#else
            strncpy(line, &str[currentCharIndex], lineSize);
#endif // ARDUINO_PROGMEM


            if (lineSize > 0) {

                vector<string> line_tokens = lex_block_char(line, lineSize);

                block b = parse_tokens(line_tokens);
                if (b.size() != 0) { //suppression des lignes vides
                    blocks.push_back(b);
                }
            }
            else {
                currentCharIndex += 1;
            }
            currentCharIndex += lineSize;
            free(line);


        }
        return blocks;

    }

    vector<block> lex_gprog_char_N(const char* str, uint16_t* currentCharIndex, uint8_t nb) {
        vector<block> blocks;
        #if DEBUG_PRINT
            Serial.print("valeur de currentcharindex : ");
            Serial.println(*currentCharIndex);
        #endif

        while (*currentCharIndex < progmemStr_GetSize(str)) {
            #if DEBUG_PRINT
                Serial.print("avant find line\n");
            #endif
            uint8_t lineSize = progmemStr_findLineSize(str, *currentCharIndex);

            char* line;
            line = (char*)realloc(NULL, lineSize);
            if (line == nullptr) {
                return vector<block>();
            }
            #if DEBUG_PRINT
                Serial.print("avant progmem copyline \n");
            #endif
            //remplir la ligne
#if ARDUINO_PROGMEM
            //remplir la ligne avec progmem
            progmemStr_CopyLine(line, lineSize, str, *currentCharIndex);
            
#else
            strncpy(line, &str[*currentCharIndex], lineSize);
#endif // ARDUINO_PROGMEM


            if (lineSize > 0) {
                #if DEBUG_PRINT
                    Serial.print("avant lexblock char\n");
                #endif
                vector<string> line_tokens = lex_block_char(line, lineSize);

                block b = parse_tokens(line_tokens);
                #if DEBUG_PRINT
                    Serial.print("Dans lex_gprog_char_20, Taille de block avec b.size(): ");
                    Serial.println(b.size());
                #endif
                if (b.size() != 0) { //suppression des lignes vides
                    blocks.push_back(b);
                }
            }
            else {
                *currentCharIndex += 1;
            }
            *currentCharIndex += lineSize;
            free(line);
            #if DEBUG_PRINT
                Serial.print("apres le free ");
                Serial.print(blocks.size());
                Serial.print(" valeur de l'index : ");
                Serial.println(*currentCharIndex);
            #endif

            if (blocks.size() == nb) {
                return blocks;
            }
            if(*currentCharIndex >= progmemStr_GetSize(str)){
                break;
            }


        }
        return blocks;

    }


    vector<block> lex_gprog(const string& str) {
        vector<block> blocks;
        string::const_iterator line_start = str.begin();
        string::const_iterator line_end;

        while (line_start < str.end()) {
            line_end = find(line_start, str.end(), '\n');
            string line(line_start, line_end);

            if (line.size() > 0) {

                vector<string> line_tokens = lex_block(line);

                block b = parse_tokens(line_tokens);
                if (b.size() != 0) { //suppression des lignes vides
                    blocks.push_back(b);
                }
            }


            line_start += line.size() + 1;
        }
        return blocks;
    }


    gcode_program parse_gcode(const std::string& program_text) {
        auto blocks = lex_gprog(program_text);
        return gcode_program(blocks);
    }

    gcode_program parse_gcode_with_char(const char* char_gcode)
    {
        auto blocks = lex_gprog_char(char_gcode);
        return gcode_program(blocks);
    }
    void parseNextN(gcode_program* prog, const char* char_gcode, uint16_t* index, uint8_t nb)
    {
        #if DEBUG_PRINT
            Serial.print("avant lex gprog char 20 taille : \n");
            Serial.println(prog->num_blocks());
        #endif
        auto blocks = lex_gprog_char_N(char_gcode, index, nb);
        #if DEBUG_PRINT
            Serial.print("apres lex gprog char 20\n");
        for(block b:blocks){
            Serial.print("taille block avant prog : ");
            Serial.println(b.size());
        }
        #endif      
        prog->addBlocks(blocks);
    }
}