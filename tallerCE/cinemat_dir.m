  function [x2,y2]=cinemat_dir(l1,l2,q1,q2)
  x2=l1*sin(q1)+l2*sin(q1+q2);
  y2=-l1*cos(q1)-l2*cos(q1+q2);
  end 
  
%    function [x2,y2,z2]=cinemat_dir(l1,l2,q1,q2,beta1,beta2)
%    x2=l1*sin(q1)+l2*sin(q1+q2)
%    y2=-l1*cos(q1)-l2*cos(q1+q2)
%    z2=beta1+beta2
%    end
%    
  

  
  
