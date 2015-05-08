Pod::Spec.new do |spec|
  spec.name         = 'SharedBase64'
  spec.version      = '1.0.1'
  spec.license      = { :type => 'Public Domain' }
  spec.homepage     = 'https://github.com/mukarev/SharedBase64'
  spec.authors      = { 'Markus Kosmal' => 'code@m-ko-x.de'}
  spec.summary      = 'Base64 implementation in C for cross-platform usage'
  
  spec.description  =  <<-DESC
    Optimized for fast string encoded binary cross-platform communication. Offers base64 encoding based on C code with several wrappers. Base 64 encoded strings will have no wrapping, no padding and are url safe. Only dependency is to <stdlib.h> to acces memory, so usable on many platforms. There is already an objective-c wrapper to use with OSX/iOS.
  DESC

  spec.source       = { :git => 'https://github.com/mko-x/SharedBase64.git', :tag => "#{spec.version}" }
  spec.source_files = 'Sources/*.{h,c}', 'Classes/*.{h,m}'
  spec.public_header_files = 'Classes/*.h'
  spec.requires_arc = true
end
