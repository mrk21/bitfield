require 'fileutils'

directory 'gen'

task :default => :test

desc 'Run the test.'
task :test => 'gen' do
  Dir.chdir('vendor') do
    sh "rake develop"
  end
  
  Dir.chdir('gen') do
    sh "cmake -D IS_EXAMPLES=false .."
    sh "make"
    
    Dir.chdir('test') do
      sh "./spec --reporter=spec"
    end
  end
end

desc 'Build examples'
task :examples => 'gen' do
  Dir.chdir('vendor') do
    sh "rake product"
  end
  
  Dir.chdir('gen') do
    sh "cmake -D IS_EXAMPLES=true .."
    sh "make"
  end
end

desc 'Clean'
task :clean => 'gen' do
  Dir.chdir('gen') do
    sh "make clean"
  end
end

desc 'Rebuild'
task :rebuild => 'gen' do
  Dir.chdir('gen') do
    sh "make clean all"
  end
end

desc 'Distclean'
task :distclean do
  FileUtils.rm_rf 'gen'
end
