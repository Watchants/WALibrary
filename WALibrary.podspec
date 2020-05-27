Pod::Spec.new do |spec|
    spec.name                   = 'WALibrary'
    spec.version                = '0.0.1'
    spec.license                = { :type => 'MIT', :file => 'LICENSE' }
    spec.author                 = { 'panghu' => 'panghu.lee@gmail.com' }
    spec.summary                = 'A short description of WALibrary.'
    spec.homepage               = 'https://github.com/Watchants/WALibrary'
    spec.source                 = { :git => 'https://github.com/Watchants/WALibrary.git', :tag => spec.version.to_s }
    
    spec.ios.deployment_target  = '10.0'
    spec.osx.deployment_target  = '10.14'
    spec.tvos.deployment_target = '10.0'

    spec.static_framework       = true
    spec.framework              = 'Foundation'
    
    spec.source_files           = 'Sources/**/*.{h,m,swift}'
    spec.module_map             = 'Sources/WALibrary.modulemap'
    spec.public_header_files    = 'Sources/WALibrary.h'
end
