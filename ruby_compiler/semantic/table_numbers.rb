module Semantic
  
  class TableNumbers
    
    @@table = {}
    
    def self.include?(token)
      @@table.include? token
    end
    
    def self.add(number)
      index = @@table.size
      value = number.to_i
      if TableNumbers.include?(value)
        index = @@table[value]
      else
        @@table[value] = index
      end
      
      return index
    end
    
  end
  
end