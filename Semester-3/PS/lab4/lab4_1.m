%pkg load statistics
clear
p = input('lil p = ');
N = input('nr of simulations = ');
for i=1:N
  r=rand;              %r=rand(1,N);
  X(i) = r<p;          %x=r<p
endfor
u_x = unique(X);
n_X = hist(X,length(u_x));   %x=[0010110] ux=[01] nx=[43]
freq = n_X/N;


