# Minishell

Minishell projesi, basit bir Unix benzeri kabuk (shell) oluşturma projesidir. Bu projede, temel kabuk işlevlerini yeniden yaratmayı hedefleyerek süreç yönetimi, dosya yönlendirme ve kullanıcı etkileşimi gibi konularda derinlemesine bilgi sahibi olacaksınız.


## Kurulum ve Çalıştırma

Proje dosyalarını derlemek ve çalıştırmak için şu adımları izleyin:

1. Depoyu klonlayın:
    ```sh
    git clone https://github.com/TufanKurukaya/Minishell.git
    cd Minishell
    ```

2. Projeyi derleyin:
    ```sh
    make
    ```

3. Minishell'i başlatın:
    ```sh
    ./minishell
    ```

## Proje Hedefleri

Minishell, temel bir kabuğun işlevlerini aşağıdaki şekilde gerçekleştirmenizi gerektirir:

1. **Prompt ve Komut Girişi**:
   - Kullanıcıdan komut beklerken bir prompt (örneğin `$ `) gösterilmelidir.
   - Kullanıcının girdiği komutlar doğru bir şekilde okunmalı ve yorumlanmalıdır.

2. **Komut Çalıştırma**:
   - PATH değişkenine göre ya da göreli/bağıl yollar kullanarak doğru çalıştırılabilir dosya bulunmalı ve çalıştırılmalıdır.
   - Komutlar, çeşitli dosya yönlendirmeleri ve pipe karakteri (`|`) ile birleştirilerek çalıştırılabilmelidir.

3. **Yerleşik Komutlar (Builtins)**:
   - Projeniz aşağıdaki yerleşik komutları desteklemelidir:
     - `echo`: Metin çıktılamak için kullanılır. `-n` seçeneği ile satır sonu karakteri bastırılabilir.
     - `cd`: Dizin değiştirmek için kullanılır.
     - `pwd`: Geçerli çalışma dizinini ekrana basar.
     - `export`: Ortam değişkenlerini ayarlamak için kullanılır.
     - `unset`: Ortam değişkenlerini kaldırmak için kullanılır.
     - `env`: Mevcut ortam değişkenlerini listeler.
     - `exit`: Kabuktan çıkmak için kullanılır.

4. **Sinyal Yönetimi**:

   - İnteraktif modda dışında:
      - `Ctrl-C`, `Ctrl-D` ve `Ctrl-\` kombinasyonları Bash'teki gibi davranmalıdır

   - İnteraktif modda:
     - `Ctrl-C`: Yeni bir prompt gösterir.
     - `Ctrl-D`: Kabuktan çıkış yapar.
     - `Ctrl-\`: Herhangi bir işlem yapmaz.

5. **Dosya Yönlendirme ve Boru (Pipe) Desteği**:
   - Giriş (`<`), çıkış (`>`), ekleme modu (`>>`) ve heredoc (`<<`) yönlendirmeleri uygulanmalıdır.
   - Pipe (`|`) karakteri kullanılarak, bir komutun çıktısı diğer bir komutun girdisi olarak kullanılmalıdır.

6. **Ortam Değişkenleri ve Özel Değişkenler**:
   - `$` ile başlayan ortam değişkenleri genişletilmeli ve değerleri komutlarda kullanılabilmelidir.
   - `$?`: En son çalıştırılan komutun çıkış durumunu geri döndürmelidir.


## Yapılması Gerekenler

Minishell projesinde başarılı olabilmek için aşağıdaki adımları izlemeniz gerekmektedir:

1. **Temel Kabuk Fonksiyonlarının Uygulanması**:
   - Prompt gösterimi ve kullanıcıdan komut alınması.
   - Girdiğiniz komutların doğru bir şekilde yorumlanarak çalıştırılması.

2. **Yerleşik Komutların (Builtins) Geliştirilmesi**:
   - Her bir yerleşik komutun tam olarak ne yapması gerektiğini anlamak ve doğru şekilde uygulamak.

3. **Sinyal Yönetimi**:
   - Sinyal işlemlerini yönetmek ve kabuğun beklenen davranışları sergilemesini sağlamak.

4. **Bellek Yönetimi**:
   - Özellikle `readline` fonksiyonunu kullanırken bellek sızıntılarından kaçınmak.
   - Tüm dinamik bellek tahsislerinin doğru bir şekilde serbest bırakıldığından emin olmak.

5. **Test ve Hata Ayıklama**:
   - Farklı senaryolarda kabuğunuzu test etmek ve hata durumlarını analiz etmek.
   - Potansiyel bellek sızıntıları veya hatalı davranışları bulmak ve düzeltmek.

Proje sonunda, bir kabuğun temel işlevlerini anlayacak, süreç yönetimi ve sinyal işlemleri konusunda derinlemesine bilgi sahibi olacaksınız.

## Bellek Yönetimi

Minishell projesinde, dinamik bellek yönetimi büyük önem taşır. Bu proje için özel olarak geliştirilmiş bir bellek yönetimi mekanizması uygulanmıştır. Bu mekanizma, heap'ten tahsis edilen tüm bellek bloklarını takip etmek için bir bağlı liste (linked list) kullanır.

### Gerekli Olabilecek Fonksiyonlar

- `malloc` fonksiyonuna benzer şekilde çalışan, ancak tahsis edilen bellek bloğunu bağlı listeye ekleyen. Bu sayede, bellek bloklarının yönetimi daha kolay hale getirecek bir fonksiyon.

- Harici olarak tahsis edilen bir bellek bloğunu bağlı listeye ekleyen bir fonksiyon. Bu fonksiyon, mevcut bellek bloğunun yönetilmesini sağlar.

- Tüm bağlı listeyi dolaşarak, listeye eklenmiş olan tüm bellek bloklarını serbest bırakan bir fonksiyon. Bu fonksiyon, program sonunda kullanılmayan tüm belleklerin temizlenmesini sağlar.

- Belirtilen bellek bloğunu bağlı listeden çıkaran ve serbest bırakan bir fonksiyon. Bu, belirli bir bellek bloğunu manuel olarak temizlemek istediğinizde kullanışlıdır.

Bu bellek yönetimi sistemi, projede bellek sızıntılarının önlenmesine yardımcı olur ve bellek kullanımını daha güvenilir hale getirir.

## Proje Bileşenleri

Minishell projesi, aşağıdaki bileşenleri içerir:

### Lexer (Lexical Analysis)
Lexer, kullanıcı tarafından girilen komutları parçalara (token'lara) ayıran bileşendir. Bu parçalar, komutların çeşitli bölümlerini (örneğin komut adı, argümanlar, operatörler) temsil eder. Lexer, girdi metnini analiz eder ve dilin sözdizimine uygun olarak farklı türlerdeki token'ları ayırır.

### Parser (Syntactic Analysis)
Parser, Lexer tarafından üretilen token'ları alır ve bunları gramer kurallarına göre yapılandırır. Bu süreç, komutların anlamlı bir şekilde yorumlanabilmesi için gereklidir. Parser, komutların doğru bir şekilde çalıştırılabilmesi için bir soyut sözdizim ağacı (AST - Abstract Syntax Tree) oluşturur.

### Expander
Expander, ortam değişkenlerinin genişletilmesi, özel karakterlerin işlenmesi ve tırnak işaretleri gibi öğelerin ele alınmasından sorumludur. Bu bileşen, komutların çalıştırılmadan önce tam olarak ne anlama geldiğini belirler. Örneğin, `$HOME` gibi bir değişkenin değeri, Expander tarafından doğru şekilde genişletilir.

### Executor
Executor, Parser tarafından oluşturulan AST'yi alır ve komutları yürütür. Bu süreçte, komutlar sırayla çalıştırılır ve gerekli olan süreçler (process) ve dosya yönlendirmeleri (I/O redirection) yönetilir. Executor, Minishell'in ana işlevselliğinin gerçekleştiği bileşendir ve komutların gerçek anlamda çalıştırılmasını sağlar.


## EXERCISE

Proje dizininizde bulunan `EXERCISE` klasöründe, Minishell projesinde sıkça kullanılan sistem çağrıları ve fonksiyonlar hakkında ayrıntılı açıklamalar ve daha rahat anlaşılmasını sağlayabilmek için yazılmış egzersizleri bulabilirsiniz. Bu bölümde, aşağıdaki gibi konular hakkında bilgi verilmektedir:

- `fork()`: Yeni bir süreç oluşturmak için kullanılır.
- `execve()`: Yeni bir program çalıştırmak için mevcut sürecin imajını değiştirmek amacıyla kullanılır.
- `pipe()`: İki süreç arasında veri akışı sağlamak için kullanılır.
- `dup2()`: Dosya tanımlayıcılarını yeniden yönlendirmek için kullanılır.
- `waitpid()`: Süreçlerin tamamlanmasını beklemek için kullanılır.

Bu klasördeki dokümantasyon, projenizde bu fonksiyonları doğru bir şekilde kullanabilmeniz için size rehberlik edecektir. Kodunuzu geliştirirken ve hataları giderirken bu bilgileri referans alabilirsiniz.

## Katkıda Bulunanlar

Bu projede katkıda bulunanlar:
- [tkurukay](https://profile.intra.42.fr/users/tkurukay)
- [idelemen](https://profile.intra.42.fr/users/idelemen)

Projeyle ilgili geri bildirimleriniz için lütfen [kurukayatufan@gmail.com](mailto:kurukayatufan@gmail.com) adresinden iletişime geçin.
