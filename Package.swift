// swift-tools-version:5.1
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "WALibrary",
    products: [
        .library(
            name: "WALibrary",
            targets: ["WALibrary"]),
    ],
    targets: [
        .target(
            name: "WALibrary",
            dependencies: []),
    ]
)
