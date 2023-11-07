clear
largo = dlmread("largo.txt");
x = dlmread("radios.csv",",");
n = length(x);

Fn(1,:)    =[];                   %frecuencia muy baja ojo.
VecP(:,1)  =[];

%Error=sqrt((Fn(1)-f_obj_1)^2 + (Fn(2)-f_obj_2)^2 + (Fn(3)-f_obj_3)^2  + (Fn(4)-f_obj_4)^2   + (Fn(5)-f_obj_5)^2 + ...
%    (Fn(6)-f_obj_6)^2 + (Fn(7)-f_obj_7)^2 + (Fn(8)-f_obj_8)^2  + (Fn(9)-f_obj_9)^2   + (Fn(10)-f_obj_10)^2);

Error=sqrt((Fn(1)-f_obj_1)^2 + (Fn(2)-f_obj_2)^2 + (Fn(3)-f_obj_3)^2  + (Fn(4)-f_obj_4)^2   + (Fn(5)-f_obj_5)^2 + ...
    (Fn(6)-f_obj_6)^2 + (Fn(7)-f_obj_7)^2);
fobj=Error;

dlmwrite ("f_obj.csv", fobj,",")