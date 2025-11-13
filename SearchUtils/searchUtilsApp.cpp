#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>
#include "searchUtils.h"

int main() {
    std::vector<int> sizes = {10000,20000,30000,40000,50000,60000,70000,80000,90000,100000};
    std::vector<int> linComps, binComps;
    linComps.reserve(sizes.size());
    binComps.reserve(sizes.size());

    for (int n : sizes) {
        auto arr = generateSortedVector(n);
        int linComp = 0, binComp = 0;
        int key = n + 1; // worst-case (not found)
        linearSearch(arr, key, linComp);
        binarySearch(arr, key, binComp);
        linComps.push_back(linComp);
        binComps.push_back(binComp);
    }

    // Write CSV backup
    std::filesystem::path outDir = std::filesystem::current_path() / "SearchUtils";
    std::filesystem::create_directories(outDir);
    std::ofstream csv(outDir / "search_results.csv");
    csv << "n,linear_comparisons,binary_comparisons\n";
    for (size_t i = 0; i < sizes.size(); ++i) {
        csv << sizes[i] << "," << linComps[i] << "," << binComps[i] << "\n";
    }
    csv.close();

    // Prepare PowerShell script to fill the docx tables using Word COM automation
    std::filesystem::path psPath = outDir / "fill_docx.ps1";
    std::filesystem::path docPath = outDir / "Searching analysis1.docx";

    std::ofstream ps(psPath);
    ps << "$ErrorActionPreference = 'Stop'\n";
    ps << "$docPath = @'" << docPath.string() << "'@\n";

    // sizes array
    ps << "$sizes = @(";
    for (size_t i = 0; i < sizes.size(); ++i) {
        if (i) ps << ",";
        ps << sizes[i];
    }
    ps << ")\n";

    // lin array
    ps << "$lin = @(";
    for (size_t i = 0; i < linComps.size(); ++i) {
        if (i) ps << ",";
        ps << linComps[i];
    }
    ps << ")\n";

    // bin array
    ps << "$bin = @(";
    for (size_t i = 0; i < binComps.size(); ++i) {
        if (i) ps << ",";
        ps << binComps[i];
    }
    ps << ")\n";

    ps << "$word = New-Object -ComObject Word.Application\n";
    ps << "$word.Visible = $false\n";
    ps << "$doc = $word.Documents.Open($docPath)\n";
    ps << "try {\n";
    ps << "  # Table 1: linear search (assumes header row + 10 data rows)\n";
    ps << "  $t1 = $doc.Tables.Item(1)\n";
    ps << "  for ($i = 0; $i -lt $lin.Count; $i++) {\n";
    ps << "    $row = $i + 2; # skip header row\n";
    ps << "    if ($row -le $t1.Rows.Count) { $t1.Cell($row, 2).Range.Text = $lin[$i].ToString() }\n";
    ps << "  }\n";
    ps << "  # Table 2: binary search\n";
    ps << "  $t2 = $doc.Tables.Item(2)\n";
    ps << "  for ($i = 0; $i -lt $bin.Count; $i++) {\n";
    ps << "    $row = $i + 2; # skip header row\n";
    ps << "    if ($row -le $t2.Rows.Count) { $t2.Cell($row, 2).Range.Text = $bin[$i].ToString() }\n";
    ps << "  }\n";
    ps << "  $doc.Save()\n";
    ps << "} finally {\n";
    ps << "  $doc.Close()\n";
    ps << "  $word.Quit()\n";
    ps << "}\n";
    ps.close();

    // Execute the PowerShell script
    std::string command = "powershell -ExecutionPolicy Bypass -File \"" + psPath.string() + "\"";
    std::cout << "Filling docx table using PowerShell (requires MS Word). Running: " << command << "\n";
    int rc = std::system(command.c_str());
    if (rc != 0) {
        std::cerr << "PowerShell script returned non-zero exit code: " << rc << "\n";
        std::cerr << "The CSV file 'SearchUtils/search_results.csv' contains the results as a fallback.\n";
        return 1;
    }

    std::cout << "Done. Results written to 'SearchUtils/search_results.csv' and docx updated.\n";
    return 0;
}
