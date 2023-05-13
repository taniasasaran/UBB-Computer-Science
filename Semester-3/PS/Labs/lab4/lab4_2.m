clear
p = input('lil p = ');
n = input('nr of trials = ');
N = input('nr of simulations = ');
r = rand(n,N);
X = sum(r < p);

u_x = unique(X);
n_X = hist(X,length(u_x));
freq = n_X/N;
%plot(u_x,freq)

k = 0:n;
p_k = binopdf(k,n,p);
plot(k,p_k,'.',u_x,freq,'*')
% theoretical values vs simulation values

