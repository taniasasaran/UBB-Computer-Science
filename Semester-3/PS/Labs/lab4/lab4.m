% A %%%%%%%%
p = input('lil p(0<p<1) = ');
N = input('big n(no of simulations) = ');
U = rand(1,N);
X = (U<p);
U_X = unique(X);
n_X = hist(X,length(U_X));
rel_freq = n_X/N;
