module Lex
  
  class Analyser
    
    def initialize(content)
      @content = content
      @fixed_content = @content + ' '
      @t = Transducer.new
      @line = 1
      @column = 0
    end
    
    def get_next_token
      token = Token.new
      type = Token::Type::IGNORED
      value = nil
      line_end = @line
      column = @column

      if @content.empty?
        token.type = Token::Type::END_OF_FILE
        return token
      end
      
      # Read ignored chars
      while @content.size > 0 and type == Token::Type::IGNORED
        # do nothing, chars are being ignored
        type = @t.consume_input(@fixed_content[0], @fixed_content[1])
        value = @content[0,1]
        @content = @content[1,@content.size]
        @fixed_content = @fixed_content[1,@fixed_content.size]
        
        @column += 1
        if value[0] == ?\n
          line_end += 1
          @column = 0
        end
      end

      @line = line_end
      column = @column
      
      # Read token
      while @content.size > 0 and type == Token::Type::INCOMPLETE
        type = @t.consume_input(@fixed_content[0], @fixed_content[1])
        value += @content[0,1]
        @content = @content[1,@content.size]
        @fixed_content = @fixed_content[1,@fixed_content.size]
        
        @column += 1
        if value[-1] == ?\n
          line_end += 1
          @column = 0
        end
      end
      
      value = nil if type == Token::Type::IGNORED
      
      if type == Token::Type::INCOMPLETE
        type = Token::Type::INVALID
      elsif type == Token::Type::IDENTIFIER and Semantic::TableReservedWords.include?(value)
        type = Token::Type::RESERVED_WORD
      end
      
      token.value = value
      token.index = table_value(value, type)
      token.type = type
      token.line = @line
      token.column = column
      
      @line = line_end
      
      return token
    end
    
    def table_value(value, type)
      index = -1
      
      if type == Token::Type::INT_NUMBER
        index = Semantic::TableNumbers.add(value)
      elsif type == Token::Type::RESERVED_WORD
        index = Semantic::TableReservedWords.index(value)
      elsif type == Token::Type::IDENTIFIER
        index = Semantic::TableSymbols.add(value)
      elsif type == Token::Type::SPECIAL
        index = Semantic::TableSpecial.index(value)
      end
      
      return index
    end
    
  end
  
end