function perfeitos(n)
   cont=0
   x=0
   print("Os numeros perfeitos sao ")
   repeat
      x=x+1
      soma=0
      for i=1,(x-1) do
         if math.mod(x,i)==0 then soma=soma+i;
         end
      end
      if soma == x then
         print(x)
         cont = cont+1
      end
   until cont==n
   print("Pressione qualquer tecla para finalizar...")
end