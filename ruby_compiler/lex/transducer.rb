module Lex
  
  class Transducer
    INVALID_STATE = -1
    EMPTY_STRING = -1
    
    attr_accessor :transitions
    
    def initialize
      @initial_state = 0
      @current_state = @initial_state
      @total_states = 1
      @available_states = 100
      @transitions = {}
      initialize_transitions
    end
    
    def initialize_transitions
      # Default transition goes to an invalid state and returns an invalid token type
      @available_states.times do |state|
        @transitions[state] = {}
        (0..255).each do |input|
          @transitions[state][input] = [INVALID_STATE, Token::Type::INVALID]
        end
        @transitions[state][EMPTY_STRING] = [INVALID_STATE, Token::Type::INVALID]
      end
      
      # spaces
      @transitions[0][' '[0]] = [0, Token::Type::IGNORED]
      @transitions[0][?\n] = [0, Token::Type::IGNORED]
      @transitions[0][?\t] = [0, Token::Type::IGNORED]
      
      # identifier
      s = _new_state
      (?a..?z).each do |l|
        @transitions[0][l] = [s, Token::Type::INCOMPLETE]
        @transitions[s][l] = [s, Token::Type::INCOMPLETE]
        (?0..?9).each do |i|
          @transitions[s][i] = [s, Token::Type::INCOMPLETE]
        end
      end
      @transitions[s][EMPTY_STRING] = [0, Token::Type::IDENTIFIER]
      
      # integer number
      s = _new_state
      (?0..?9).each do |i|
        @transitions[0][i] = [s, Token::Type::INCOMPLETE]
        @transitions[s][i] = [s, Token::Type::INCOMPLETE]
      end
      @transitions[s][EMPTY_STRING] = [0, Token::Type::INT_NUMBER]
      
      # comments
      s = _new_state
      @transitions[0]['%'] = [s, Token::Type::IGNORED]
      (0..255).each do |i|
        @transitions[s][i] = [s, Token::Type::IGNORED]
      end
      @transitions[s][?\n] = [0, Token::Type::IGNORED]
      
      # special
      @transitions[0][?:] = [0, Token::Type::SPECIAL]
      @transitions[0][?;] = [0, Token::Type::SPECIAL]
      @transitions[0][?+] = [0, Token::Type::SPECIAL]
      @transitions[0][?-] = [0, Token::Type::SPECIAL]
      @transitions[0][?*] = [0, Token::Type::SPECIAL]
      @transitions[0][?/] = [0, Token::Type::SPECIAL]
      @transitions[0][?(] = [0, Token::Type::SPECIAL]
      @transitions[0][?)] = [0, Token::Type::SPECIAL]
      @transitions[0][?.] = [0, Token::Type::SPECIAL]
      
      #
      # The next special chars are nondeterministic
      # with dept 2
      #
      
      # = ==
      s = _new_state
      @transitions[0][?=] = [s, Token::Type::INCOMPLETE]
      @transitions[s][?=] = [0, Token::Type::SPECIAL]
      @transitions[s][EMPTY_STRING] = [0, Token::Type::SPECIAL]
      
      # > >=
      s = _new_state
      @transitions[0][?>] = [s, Token::Type::INCOMPLETE]
      @transitions[s][?=] = [0, Token::Type::SPECIAL]
      @transitions[s][EMPTY_STRING] = [0, Token::Type::SPECIAL]
      
      # < <=
      s = _new_state
      @transitions[0][?<] = [s, Token::Type::INCOMPLETE]
      @transitions[s][?=] = [0, Token::Type::SPECIAL]
      @transitions[s][EMPTY_STRING] = [0, Token::Type::SPECIAL]
      
    end
    
    def _new_state
      @total_states+=1
      return @total_states - 1
    end
    
    def consume_input(input, lookahead)
      next_state,token_type = @transitions[@current_state][input]
      
      #print "(#{@current_state}) #{input}, #{lookahead} => #{next_state}"
      
      if next_state == -1
        token_type = Token::Type::INVALID
        next_state = 0
      elsif token_type == Token::Type::INCOMPLETE and @transitions[next_state][lookahead][0] == INVALID_STATE
        token_type = @transitions[next_state][EMPTY_STRING][1]
        next_state = 0
      end
      
      @current_state = next_state
      
      #puts ", #{token_type} (#{@current_state}) - #{Token::Type.name(token_type)}"
      
      return token_type
    end
    
  end
  
end