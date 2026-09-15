platform :ios, '15.0'

source 'https://cdn.cocoapods.org/'

# TopOn 聚合建议静态链接，避免与三方广告 SDK 动态库冲突
# Meta Audience Network 由 Facebook Adapter 拉取；其余为 TopOn 官方 Adapter
use_frameworks! :linkage => :static

target 'excat_nonogarm' do
  # TopOn 核心
  pod 'TPNiOS', '6.5.80'

  # TopOn ADX（必要）
  pod 'TPNMediationAdxSmartdigimktAdapter', '6.5.78.2.0'

  # 广告源 Adapter：Vungle / Bigo / Meta / InMobi / Chartboost / DT(Fyber)
  pod 'TPNMediationVungleAdapter', '7.7.6.2.0'
  pod 'TPNMediationBigoAdapter', '5.3.0.2.0'
  pod 'TPNMediationFacebookAdapter', '6.22.0.2.1'
  pod 'TPNMediationInmobiAdapter', '11.1.1.2.1'
  pod 'TPNMediationChartboostAdapter', '9.11.0.2.1'
  pod 'TPNMediationFyberAdapter', '8.4.7.2.0'
end

post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      config.build_settings['ENABLE_USER_SCRIPT_SANDBOXING'] = 'NO'
      config.build_settings['CLANG_WARN_DOCUMENTATION_COMMENTS'] = 'NO'
      config.build_settings['IPHONEOS_DEPLOYMENT_TARGET'] = '15.0'
      config.build_settings['SWIFT_VERSION'] = '5.0'
    end
  end

  installer.aggregate_targets.each do |aggregate_target|
    aggregate_target.user_project.targets.each do |target|
      target.build_configurations.each do |config|
        config.build_settings['ENABLE_USER_SCRIPT_SANDBOXING'] = 'NO'
        config.build_settings['CLANG_WARN_DOCUMENTATION_COMMENTS'] = 'NO'
        config.build_settings['SWIFT_VERSION'] = '5.0'
      end
    end
    aggregate_target.user_project.save
  end
end
