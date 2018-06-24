cd test-result/ctest
$XSLInputElement = New-Object System.Xml.Xsl.XslCompiledTransform
$XSLInputElement.Load("https://raw.githubusercontent.com/rpavlik/jenkins-ctest-plugin/master/ctest-to-junit.xsl")
$XSLInputElement.Transform((Resolve-Path .\Test.xml), (Join-Path (Resolve-Path .) "ctest-to-junit-results.xml"))
$wc = New-Object 'System.Net.WebClient'
$wc.UploadFile("https://ci.appveyor.com/api/testresults/junit/$($env:APPVEYOR_JOB_ID)", (Resolve-Path .\ctest-to-junit-results.xml))
cd ..
foreach ($file in get-ChildItem *.xml)
{
    echo $file.name
    $wc.UploadFile("https://ci.appveyor.com/api/testresults/junit/$($env:APPVEYOR_JOB_ID)", (Resolve-Path $file.name))
}
echo "finish"
