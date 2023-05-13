%comm

n=30;
p=0.5;
%n=input('Nr of trials=');
%p=input('Prob of success=');
x=0:n;
p1=binopdf(0,3,0.5);
fprintf('%1.4f\n',p1)
y=binopdf(x,n,p);
plot(x,y,'+');


hold on


xx = 0:0.01:n;
yy=binocdf(xx,n,p);
plot(xx,yy);

p2=binocdf(2,3,0.5);
fprintf('%1.4f\n',p2);

p3=binocdf(1,3,0.5);
fprintf('%1.4f\n',p3);

p4=1-binopdf(0,3,0.5);
fprintf('%1.4f\n',p4);

p5=1-binocdf(1,3,0.5);
fprintf('%1.4f\n',p5);

rand()<0.5;

C=rand(3,100000);

D = C<0.5;
E = sum(D);
hist(E)

