Bu proje, derslerin section (şube) sayılarına göre öğretim üyeleri arasında dengeli bir şekilde dağıtılmasını amaçlayan bir C programıdır.
Programda her ders için sınav zamanı ve sınav süresi dikkate alınarak bir ders yükü hesaplanmaktadır. Ayrıca öğretim üyelerinin kıdem bilgileri de hesaba katılarak toplam iş yükünün adil biçimde paylaşılması hedeflenmektedir.
Dersler ve öğretim üyeleri başlangıçta rastgele karıştırılmakta, ardından her ders section sayısı kadar en az yüke sahip olan öğretim üyesine atanmaktadır.
Ders ataması sırasında öğretim üyesinin mevcut toplam yükü ve kıdem katsayısı birlikte değerlendirilerek karar verilmektedir. Böylece belirli bir öğretim üyesinin aşırı yük altında kalması engellenmektedir.
Program çalıştırıldığında her öğretim üyesinin aldığı dersler ve toplam yük bilgileri ekrana yazdırılmaktadır. Ayrıca her dersin hangi öğretim üyelerine atandığı da ayrı bir bölümde gösterilmektedir. 
Proje, yük dengeleme (load balancing) mantığını temel alan basit bir dağıtım algoritması örneği sunmaktadır ve eğitim amaçlı olarak geliştirilmiştir. 


**Derleme ve Çalıştırma**

gcc ders_dagitimi.c -o ders_dagitimi
./ders_dagitimi

**Çıktı**
Program çalıştırıldığında: <br>
Her hocanın aldığı dersler <br>
Hocaların toplam yükleri <br>
Ders → Hoca eşleşmeleri <br>

ekrana yazdırılır.
