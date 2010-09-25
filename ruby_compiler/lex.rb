require 'lex/token'
require 'lex/transducer'
require 'lex/analyser'

module Lex
  
  def self.example
    
    input = File.read('../resources/test_lex.poli')
    
    analyser = Lex::Analyser.new(input)
    while (token = analyser.get_next_token).type != Token::Type::END_OF_FILE
      puts token.to_str
    end

  end
  
end