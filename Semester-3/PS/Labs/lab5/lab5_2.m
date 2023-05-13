clear
%ones = [3*ones(1,5),6]


p = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
r = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

printf('case sigma1 = sigma2 difference of the true means\n');
oneminusalfa = input('how confident are ya? (0<c<1) = ');
alfa = 1-oneminusalfa;

p_mean = mean(p);
n1 = length(p);
s1 = std(p);
r_mean = mean(r);
n2 = length(r);
s2 = std(r);
sp = sqrt( ((n1-1)*s1*s1 +(n2-1)*s2*s2) / (n1+n2-2) );
t1minusalfaover2 = tinv(1-alfa/2,n1+n2-2);
talfaover2 = tinv(alfa/2,n1+n2-2);

m1 = p_mean - r_mean - t1minusalfaover2*sp*sqrt(1/n1+1/n2);
m2 = p_mean - r_mean + t1minusalfaover2*sp*sqrt(1/n1+1/n2);
printf('The confidence interval of the difference of the two means when sigma is unknown is (%4.3f   %4.3f)\n',m1,m2);

s12 = var(p);
s22 = var(r);
c = (s12/n1)/(s12/n1+s22/n2);
n = 1/(c*c/(n1-1)+(1-c)*(1-c)/(n2-1));
t1minusalfaover2 = tinv(1-alfa/2,n);
talfaover2 = tinv(alfa/2,n);

m1 = p_mean - r_mean - t1minusalfaover2*s12*sqrt(s12/n1+s22/n2);
m2 = p_mean - r_mean + t1minusalfaover2*s22*sqrt(s12/n1+s22/n2);
printf('The confidence interval of the diff (%4.3f   %4.3f)\n',m1,m2);




