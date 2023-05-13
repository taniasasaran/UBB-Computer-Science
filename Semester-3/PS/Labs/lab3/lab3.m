%pkg load statistics
alfa =input('alfa=');
beta = input('beta=');
option = input('option=','s');
switch option
  case 'normal'
    miu=input('miu=');
    sigma=input('sigma=');
    p1 = normcdf(0,miu,sigma)
    p2 = 1 - p1
    p3 = normcdf(1,miu,sigma) - normcdf(-1,miu,sigma)
    p4 = 1 - p3
    inv = norminv(alfa,miu,sigma)
    binv = norminv(1-beta,miu,sigma)

 case 'stud'
    n=input('n=');
    p1 = tcdf(0,n)
    p2 = 1 - p1
    p3 = tcdf(1,n) - tcdf(-1,n)
    p4 = 1 - p3
    inv = tinv(alfa,n)
    binv = tinv(1-beta,n)

  case 'fisher'
    n=input('n=');
    m=input('m=');
    p1 = fcdf(0,m,n)
    p2 = 1 - p1
    p3 = fcdf(1,m,n) - fcdf(-1,m,n)
    p4 = 1 - p3
    inv = finv(alfa,m,n)
    binv = finv(1-beta,m,n)

   otherwise fprintf('Error\n')
end




