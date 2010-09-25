module Semantic
  
  class TableSymbols
    
    @@table = {}
    
    def self.include?(token)
      @@table.include? token
    end
    
    def self.add(symbol)
      index = @@table.size
      if TableSymbols.include?(symbol)
        index = @@table[symbol]
      else
        @@table[symbol] = index
      end
      
      return index
    end
    
  end
  
end