clear

x = [7, 7, 4, 5, 9, 9, ...
4, 12, 8, 1, 8, 7, ...
3, 13, 2, 1, 17, 7, ...
12, 5, 6, 2, 1, 13, ...
14, 10, 2, 4, 9, 11, ...
3, 5, 12, 6, 10, 7];
n = length(x);
oneminusalfa = input('how confident are ya? (0<c<1) = ');
alfa = 1-oneminusalfa;
samp_mean = mean(x);
printf('solving 1a\n');
sigma = 5;
inv = norminv(1-alfa/2,0,1);
m1 = samp_mean - sigma/sqrt(n)*norminv(1-alfa/2,0,1);
m2 = samp_mean - sigma/sqrt(n)*norminv(alfa/2,0,1);
m3 = samp_mean + sigma/sqrt(n)*norminv(1-alfa/2,0,1);
printf('The confidence interval of the mean when sigma=5 is (%4.3f   %4.3f)\n',m1,m2);


printf('solving 1b\n');
s = std(x);
inv = tinv(1-alfa/2,n-1);
m1 = samp_mean - s/sqrt(n)*tinv(1-alfa/2,n-1);
m2 = samp_mean - s/sqrt(n)*tinv(alfa/2,n-1);
m3 = samp_mean + s/sqrt(n)*tinv(1-alfa/2,n-1);
printf('The confidence interval of the mean when sigma is unknown is (%4.3f   %4.3f)\n',m1,m2);


printf('solving 1c\n');
ss = var(x);
v1 = chi2inv(1-alfa/2,n-1);
v2 = chi2inv(alfa/2,n-1);
m1 = (n-1)*ss/chi2inv(1-alfa/2,n-1);
m2 = (n-1)*ss/chi2inv(alfa/2,n-1);
printf('The confidence interval for variance (%4.3f   %4.3f)\n',m1,m2);

s1=sqrt(m1);
s2=sqrt(m2);
printf('The confidence interval for std variation (%4.3f   %4.3f)\n',s1,s2);
















