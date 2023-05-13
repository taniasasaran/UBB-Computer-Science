clear
p = input('lil p = ');
N = input('nr of simulations = ');
for i=1:N;
  x(i)=0;
  while(rand>=p);
    x(i) = x(i)+1;
  endwhile
endfor

u_x = unique(x);
n_x = j=hist(x,length(u_x));
k=0:25;
p_k = geopdf(k,p);

plot(k,p_k,'.',u_x,n_x/N,'*')

