%pkg load statistics
p = input('(0.05<=p<=0.95) p=');
for n=1:3:100
  k=0:n;
  y=binopdf(k,n,p);
  miu = n*p;
  sigma = sqrt(n*p*(1-p));
  yy=normpdf(k,miu,sigma);
  plot(k,y,'g',k,yy,'r');
  pause(0.3)
endfor

n = input('greaaaaat n=');
p = input('(p<=0.05) p=');
k=0:n;
y=binopdf(k,n,p);
lambda = n*p;
yy=poisspdf(k,lambda);
plot(k,y,'g',k,yy,'r');
pause(0.3)






