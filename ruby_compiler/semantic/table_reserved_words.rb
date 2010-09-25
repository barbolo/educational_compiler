module Semantic
  
  class TableReservedWords
    
    @@table = {
      'if' => 0,
      'else' => 1,
      'for' => 2
    }
    
    def self.include?(token)
      @@table.include? token
    end
    
    def self.index(token)
      @@table[token]
    end
    
  end
  
end