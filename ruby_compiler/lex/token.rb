module Lex
  
  class Token
    
    class Type
      INVALID = -1
      INCOMPLETE = 0
      RESERVED_WORD = 1
      IDENTIFIER = 2
      INT_NUMBER = 3
      SPECIAL = 4
      IGNORED = 5 # blank char, \n, \t, comments
      END_OF_FILE = 6 # this is a special token type, that belongs to the tokens returned when the file content has been all read
      
      @@names = {
        INVALID => 'invalid',
        INCOMPLETE => 'incomplete',
        RESERVED_WORD => 'reserved word',
        IDENTIFIER => 'identifier',
        INT_NUMBER => 'integer number',
        SPECIAL => 'special char',
        IGNORED => 'ignored char',
        END_OF_FILE => 'end of file'
      }
      
      def self.name(type)
        @@names[type]
      end
      
    end
    
    attr_accessor :type, :value, :index, :line, :column
    
    def type_name
      Type.name(type)
    end
    
    def to_str
      "#{value} (#{index}) :: #{type_name} (#{type}) :: line #{line}, column #{column}"
    end
    
  end
  
end