//
//  SwiftAdLinkStub.swift
//  excat_nonogarm
//
//  Ensures Swift compatibility libs are linked when archiving
//  against static Swift ad SDKs (Chartboost / Vungle / Fyber) on CI.
//

import Foundation

enum SwiftAdLinkStub {
    static let marker = "linked"
}
