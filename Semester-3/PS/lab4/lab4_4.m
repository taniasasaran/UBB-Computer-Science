clear

p = input('lil p = ');
n = input('nr of successes = ');
N = input('nr of simulations = ');

for i=1:N
  for j=1:n
    x(j)=0;
    while rand>=p;
      x(j) = x(j)+1;  %am numarat cate failuri avem
    endwhile
  endfor
  y(i)=sum(x);
endfor

u_y = unique(y);
n_y = hist(y,length(u_y));
freq = n_y/N;
%plot(u_y,freq)

k=0:100;
p_k = nbinpdf(k,n,p);
plot(k,p_k,'.',u_y,freq,'*')

