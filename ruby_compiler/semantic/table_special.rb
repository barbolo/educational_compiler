module Semantic
  
  class TableSpecial
    
    @@table = {
      ':' => 0,
      ';' => 1,
      '+' => 2,
      '-' => 3,
      '*' => 4,
      '/' => 5,
      '(' => 6,
      ')' => 7,
      '.' => 8,
      '=' => 9,
      '==' => 10,
      '>' => 11,
      '>=' => 12,
      '<' => 13,
      '<=' => 14
    }
    
    def self.include?(token)
      @@table.include? token
    end
    
    def self.index(token)
      @@table[token]
    end
    
  end
  
end